Dim fso, tx, source

Set objArgs = WScript.Arguments

set fso = CreateObject("Scripting.FileSystemObject")

set tx = fso.CreateTextFile(objArgs(1), True)

set source = CreateObject("Shell.Application").NameSpace(objArgs(0)).Items

For Each file in source 
	tx.WriteLine(file)
Next
tx.Close