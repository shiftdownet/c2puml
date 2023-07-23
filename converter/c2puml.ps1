
#
# 超ゴリ押し力技
#
Param([String]$codeRootPath = "./../demo/example", [String]$outPath = "./../demo/sample_code.iuml", [String]$codeEncoding = "UTF8")

class c2puml {
    [String]$convertedString = ""
    [Int32]$nest = 0

    [void]startParse( [String]$rootPath, [String]$outPath, [String]$codeEncoding ) {
        $this.Write("@startuml")

        $files = Get-ChildItem -Path $rootPath -Recurse -Filter "*.c"
        foreach ( $file in $files ) {
            $rootFullPath = Resolve-Path $rootPath
            $parentDirName = ($file.FullName).Replace([String]$rootFullPath + "`\", "")
            $parentDirName = $parentDirName.Replace("`\" + $file.Name, "")
            $parentDirName = $parentDirName.Replace("`\", ".")
            # $parentDirName = Split-Path (Split-Path $file.FullName -Parent) -Leaf
            $this.Write( "'#==============================================================================================")
            $this.Write( "'# file : $($file.FullName)")
            $this.Write( "'#==============================================================================================")
            $this.Write( "`$start_component(`"$parentDirName`")")
            $this.Write( "`$start_module(`"$($file.Name)`")")

            $this.Write( "")
            switch ( $codeEncoding ) {
                "Default" {
                    $contents = Get-Content $file.FullName -Raw -Encoding Default
                }
                "UTF8" {
                    $contents = Get-Content $file.FullName -Raw -Encoding UTF8
                }
                Default {
                    $contents = Get-Content $file.FullName -Raw
                }
            }
            $contents = Get-Content $file.FullName -Raw -Encoding Default
            $this.analyzeModule( $contents, $file.Name )
            $this.Write( "")
        }

        $this.Write("' `$display_outline()")
        $this.Write("' `$call(`"EntryPoint`")")

        $this.Write("@enduml")

        $UTF8woBOM = New-Object "System.Text.UTF8Encoding" -ArgumentList @($false)
        [System.IO.File]::WriteAllLines((Join-Path $PWD $outPath), @($this.convertedString), $UTF8woBOM)
    }


    [void]analyzeModule( [String]$contents, [String]$module ) {
        $contents = $contents -Replace "/\*.*\*/", ""
        $contents = $contents -Replace "//.*?\n", ""

        $lineStart = "\n"
        $storageType = "(?<storage>(static|extern|STATIC|EXTERN)\s)?"
        $functionType = "(?<type>([^\s{};#][^+-/^&%{}]+?))"
        $functionName = "(?<name>([a-zA-Z_][a-zA-Z0-9_]+))"
        $parameters = "(?<param>(\([a-zA-Z0-9\s,_*()\[\]]+\)))"
        $functionReg = "$($lineStart)$($storageType)$($functionType)\s?$($functionName)\s?($parameters)\s*?\{(?<imp>[\s\S]+?)$lineStart}"

        $funcHead = $contents | Select-String -Pattern $functionReg -AllMatches

        foreach ( $a_match in $funcHead.Matches ) {
            $headline = "$($a_match.Groups['storage']) ## $($a_match.Groups['type']) ## $($a_match.Groups['name']) ## $($a_match.Groups['param'])" -Replace '\s+', ' '

            Write-Host ("'#----------------------------------------------------")
            Write-Host ("'# func : $headline")
            Write-Host ("'#----------------------------------------------------")

            if ( $a_match.Groups['storage'] -match "(STATIC|static)" ) {
                $procedureName = ($module -Replace "\.", "_") + "_____" + $a_match.Groups['name']
                $scope = "static"
            }
            else {
                $procedureName = $a_match.Groups['name']
                $scope = "extern"
            }

            $this.Write("'#----------------------------------------------------")
            $this.Write("'# func : $headline")
            $this.Write("'#----------------------------------------------------")
            $this.Write("`$start_func(`"$($a_match.Groups['name'])`", `"$scope`")")
            $this.Write("!procedure `$$($procedureName)()")
            $this.nest++
            $this.analyzeFunction($a_match.Groups["imp"])
            $this.nest--
            $this.Write( "!endprocedure")
            $this.Write( "")
        }
    }

    [void]analyzeFunction( [String]$funcImp ) {
        $processed = $funcImp
        $processed = $processed -Replace "\s+", " "
        $processed = $processed -Replace "\n ", "\n"

        $processed = $processed -Replace "{", "`n{`n"
        $processed = $processed -Replace "}", "`n}`n"
        $processed = $processed -Replace "}\s*else\s+if\s*\((?<exp>.*)\)\s*{", "`$elseif(`"`$1`")`n"
        $processed = $processed -Replace "}\s*else\s*{", "`$else()`n"

        $processed = $processed -Replace "\s*case\s+(.*?):", "`n`$case(`"`$1`")`n"
        $processed = $processed -Replace "\s*default:", "`n`$default()`n"
        $processed = $processed -Replace "; (if|while|for|switch|do)", ";`n`$1"


        $complexStatements = $processed.split("`n")
        
        $stack = [System.Collections.ArrayList]::new()

        $marker = $false
        foreach ( $complexStatement in $complexStatements ) {
            Write-Host $complexStatement
            #Write-Host $line
            if ( $complexStatement -match "^\s*\`$") {
                $this.nest--
                $this.Write($complexStatement)
                $this.nest++
            }
            else {
                if ($complexStatement -match "^\s*do\s*$") {
                    $stack.Add("loop")
                    $this.Write("`$loop(`"`do-while not supported`")")
                    $marker = $true
                }
                elseif ( $complexStatement -match "([^a-z]|^)(?<ctrl>if|while|for|switch|do)\s*\(\s*(?<exp>.*)\s*\)") {
                    $stack.Add($Matches["ctrl"])
                    $this.Write( ("`${0}(`"{1}`")" -f $Matches["ctrl"], $Matches["exp"]) )
                    $marker = $true
                }
                else {
                    if ( $complexStatement -match "{" ) {
                        if ($marker) {
                            Write-Host ("{0} starts" -f $stack[ $stack.Count - 1 ])
                        }
                        else {
                            $stack.add("block")
                        }
                        $this.nest++
                    }
                    elseif ( $complexStatement -match "}" ) {
                        $this.nest--
                        $poped = $stack[ $stack.Count - 1 ]
                        if ($poped -ne "block") {
                            Write-Host ($poped)
                            $this.Write( ("`$end{0}()" -f $stack[ $stack.Count - 1 ]) )
                        }
                        $stack.RemoveAt($stack.Count - 1)
                    }
                    else {
                        $lines = $complexStatement -Replace ";", ";`n"
                        $lines = $lines -Replace ":", ":`n"
                        $lines = $lines.split("`n")
                        foreach ( $line in $lines ) {
                            #Write-Host $line
                            if ( $line -match "^\s*return((\s+\(?|\(?)(?<ret>.*))?;" ) {
                                $this.Write( ("`$return(`"{0}`")" -f $Matches["ret"]) )
                            }
                            elseif ( $line -match "(?<func>[a-zA-Z0-9_]+)\s*\((?<param>.*)\)\s*;" ) {
                                $this.Write( ("`$call(`"{0}`")" -f $Matches["func"]) )
                            }
                            elseif ( $line -match "\(\s*\*\s*(?<func>[a-zA-Z0-9_]+)\s*\)\s*\((?<param>.*)\)\s*;" ) {
                                $this.Write( ("`$call(`"{0}`")" -f $Matches["func"]) )
                            }
                            elseif ( $line -match "^\s*\`$") {
                                $this.nest--
                                $this.Write($line)
                                $this.nest++
                            }
                            elseif ( $line -match "^\s*$" ) {
                            }
                            elseif ( $line -match "[=+-]" ) {
                                $this.Write("`$step(`"$line`")")
                            }
                            else {
                            }
                        }
                    }
                }
            }
        }
        #Write-Host "$processed"
    }

    [void]Write($str) {
        $this.convertedString += ("    " * $this.nest) + $str + "`n"
    }
}

$simpleConverter = [c2puml]::new()
$simpleConverter.startParse( $codeRootPath, $outPath, $codeEncoding )

