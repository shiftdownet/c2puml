
#
# 超ゴリ押し力技
#


class c2puml {
    [String]$convertedString = ""
    [Int32]$nest = 0

    [void]startParse( [String]$rootPath ) {
        $this.Write("@startuml")

        Get-ChildItem -Path $rootPath -Recurse -Filter "*.c" | ForEach-Object {
            $parentDirName = Split-Path (Split-Path $_.FullName -Parent) -Leaf
            $this.Write( "'#==============================================================================================")
            $this.Write( "'# file : $($_.FullName)")
            $this.Write( "'#==============================================================================================")
            $this.Write( "`$start_component(`"$parentDirName`")")
            $this.Write( "`$start_module(`"$($_.Name)`")")
            $this.Write( "")

            $contents = Get-Content $_.FullName -Raw -Encoding Default
            $this.analyzeModule( $contents )
            $this.Write( "")
        }

        $this.Write("' `$box()")
        $this.Write("' `$call(`"EntryPoint`")")

        $this.Write("@enduml")

        $UTF8woBOM = New-Object "System.Text.UTF8Encoding" -ArgumentList @($false)
        [System.IO.File]::WriteAllLines((Join-Path $PWD "./../demo/sample_code.iuml"), @($this.convertedString), $UTF8woBOM)
    }


    [void]analyzeModule( [String]$contents ) {
        $contents = $contents -Replace "/\*.*\*/", ""
        $contents = $contents -Replace "//.*?\n", ""

        $lineStart = "\n"
        $functionTypeAndStrageInfo = "([^\s{};#][^+-/^&%{}]+?)"
        $functionName = "[a-zA-Z_][a-zA-Z0-9_]+"
        $parameters = "\([a-zA-Z0-9\s,_*()\[\]]+\)"
        $functionReg = "$lineStart(?<type>$functionTypeAndStrageInfo)\s?(?<name>$functionName)\s?(?<param>$parameters)\s*?\{(?<imp>[\s\S]+?)$lineStart}"

        $funcHead = $contents | Select-String -Pattern $functionReg -AllMatches

        foreach( $matches in $funcHead.Matches ) {
            $headline = "$($matches.Groups['type']) $($matches.Groups['name']) $($matches.Groups['param'])"  -Replace '\s+',' '

            Write-Host ("'#----------------------------------------------------")
            Write-Host ("'# func : $headline")
            Write-Host ("'#----------------------------------------------------")

            $this.Write("'#----------------------------------------------------")
            $this.Write("'# func : $headline")
            $this.Write("'#----------------------------------------------------")
            $this.Write("`$start_func(`"$($matches.Groups['name'])`")")
            $this.Write("!procedure `$$($matches.Groups['name'])()")
            $this.nest++
            $this.analyzeFunction($matches.Groups["imp"])
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
                if($complexStatement -match "^\s*do\s*$"){
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
                        if($marker){
                            Write-Host ("{0} starts" -f $stack[ $stack.Count - 1 ])
                        }else{
                            $stack.add("block")
                        }
                        $this.nest++
                    } elseif ( $complexStatement -match "}" ) {
                        $this.nest--
                        $poped = $stack[ $stack.Count - 1 ]
                        if($poped -ne "block") {
                            Write-Host ($poped)
                            $this.Write( ("`$end{0}()" -f $stack[ $stack.Count - 1 ]) )
                        }
                        $stack.RemoveAt($stack.Count - 1)
                    }
                    else {
                        $lines = $complexStatement -Replace ";", ";`n"
                        $lines = $lines -Replace ":", ":`n"
                        $lines = $lines.split("`n")
                        foreach ( $line in $lines ){
                            #Write-Host $line
                            if ( $line -match "return\s?(?<ret>.*)?;" ) {
                                $this.Write( ("`$return(`"{0}`")" -f $Matches["ret"]) )
                            }elseif ( $line -match "(?<func>[a-zA-Z0-9_]+)\s*\((?<param>.*)\)\s*;" ) {
                                $this.Write( ("`$call(`"{0}`")" -f $Matches["func"]) )
                            }elseif ( $line -match "^\s*\`$") {
                                $this.nest--
                                $this.Write($line)
                                $this.nest++
                            }elseif ( $line -match "^\s*$" ){
                            }else{
                                $this.Write("`$step(`"$line`")")
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

#$contents = Get-Content $filePath -Raw -Encoding Default

$rootPath = "./../demo/example"

$simpleParser = [c2puml ]::new()


$simpleParser.startParse( $rootPath )

