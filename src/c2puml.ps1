
#
# 超ゴリ押し力技
#


class c2puml {
    [String]$convertedString = ""

    [void]startParse( [String]$rootPath ) {
        $this.Write("@startuml")

        Get-ChildItem -Path $rootPath -Recurse -Filter "*.c" | ForEach-Object {
            $parentDirName = Split-Path (Split-Path $_.FullName -Parent) -Leaf
            $this.Write( "'#==============================================================================================")
            $this.Write( "'# $($_.FullName)")
            $this.Write( "'#==============================================================================================")
            $this.Write( "`$start_component(`"$parentDirName`")")
            $this.Write( "`$start_module(`"$($_.Name)`")")
            $this.Write( "")

            $contents = Get-Content $_.FullName -Raw -Encoding Default
            $this.analyzeModule( $contents )
            $this.Write( "")
        }

        $this.Write("`$box()")
        $this.Write("`$call(`"EntryPoint`")")

        $this.Write("@enduml")

        $UTF8woBOM = New-Object "System.Text.UTF8Encoding" -ArgumentList @($false)
        [System.IO.File]::WriteAllLines((Join-Path $PWD "converted.md"), @($this.convertedString), $UTF8woBOM)
    }


    [void]analyzeModule( [String]$contents ) {
        $lineStart = "\r\n"
        $functionTypeAndStrageInfo = "([^+-/^&%]+?)"
        $functionName = "[a-zA-Z_][a-zA-Z0-9_]+"
        $parameters = "\([a-zA-Z\s,_*]+\)"
        $functionReg = "$lineStart(?<type>$functionTypeAndStrageInfo)\s?(?<name>$functionName)\s?(?<param>$parameters)\s*?\{(?<imp>[\s\S]+?)$lineStart}"

        $funcHead = $contents | Select-String -Pattern $functionReg -AllMatches

        $funcHead.Matches | ForEach {
            Write-Host "------" $_.Groups['name']

            $this.Write("'#===============================================")
            $this.Write("'# $($_.Groups['type']) $($_.Groups['name']) $($_.Groups['param'] -Replace '\s','')")
            $this.Write("'#===============================================")
            $this.Write("`$start_func(`"$($_.Groups['name'])`")")
            $this.Write("!procedure `$$($_.Groups['name'])()")
            $this.analyzeFunction($_.Groups["imp"])
            $this.Write( "!endprocedure")
            $this.Write( "")
        }
    }

    [void]analyzeFunction( [String]$funcImp ) {
        $processed = $funcImp
        $processed = $processed -Replace "/\*.*\*/", ""
        $processed = $processed -Replace "//.*?\n", ""
        $processed = $processed -Replace "\s+", " "
        $processed = $processed -Replace "\n ", "\n"

        $processed = $processed -Replace "\s*}\s*else\s+if\s*\((?<exp>.*)\)\s*{", "`$else(`"`$1`")`n"
        $processed = $processed -Replace "\s*}\s*else\s*{", "`$else()`n"
        $processed = $processed -Replace "\s*case\s+(.*):", "`$case(`"`$1`")`n"
        $processed = $processed -Replace "\s*default:", "`$default()`n"
        $processed = $processed -Replace "; (if|while|for|switch|do)", ";`n`$1"
        $processed = $processed -Replace "{", "`n{`n"
        $processed = $processed -Replace "}", "`n}`n"
        $complexStatements = $processed.split("`n")
        
        $stack = [System.Collections.ArrayList]::new()

        foreach ( $complexStatement in $complexStatements ) {
            #Write-Host $complexStatement
            #Write-Host $line
            if ( $complexStatement -match "^\s*\`$") {
                $this.Write($complexStatement)
            }
            else {
                
                if ( $complexStatement -match "(?<ctrl>if|while|for|switch|do)\s*\(\s*(?<exp>.*)\s*\)") {
                    $stack.Add($Matches["ctrl"])
                    $this.Write( ("`${0}(`"{1}`")" -f $Matches["ctrl"], $Matches["exp"]) )
                }
                else {
                    if ( $complexStatement -match "{" ) {
                        #Write-Host ("{0} starts" -f $stack[ $stack.Count - 1 ])
                    } elseif ( $complexStatement -match "}" ) {
                        #Write-Host ("{0} ends" -f $stack[ $stack.Count - 1 ])

                        $this.Write( ("`$end{0}()" -f $stack[ $stack.Count - 1 ]) )
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
                            }
                        }
                    }
                }
            }
        }
        #Write-Host "$processed"
    }

    [void]Write($str) {
        $this.convertedString += $str + "`n"
    }
}

#$contents = Get-Content $filePath -Raw -Encoding Default

$rootPath = "./../example"

$simpleParser = [c2puml ]::new()


$simpleParser.startParse( $rootPath )

