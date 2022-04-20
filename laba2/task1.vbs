Set objArgs = WScript.Arguments ' Массив аргументов
InputFolder = objArgs(0) ' Путь какую папку архивировать 
OutputFolder = objArgs(1) ' Путь куда архивировать

ZipFile = OutputFolder & "\" & objArgs(2)

Set fso = CreateObject("Scripting.FileSystemObject")
Set ts = fso.CreateTextFile(ZipFile, True)
ts.Write "PK" & Chr(5) & Chr(6) & String( 18, Chr(0))
ts.Close

Set zip = CreateObject("Shell.Application").NameSpace(ZipFile)

Set sourceItems = CreateObject("Shell.Application").NameSpace(InputFolder).Items

For Each item in sourceItems
	If fso.GetExtensionName(InputFolder & "\" & item) = objArgs(3) Then
		zip.CopyHere(item)
		WScript.Sleep 1000 
	End If
Next

WSH.echo "Done!"