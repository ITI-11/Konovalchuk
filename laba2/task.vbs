Set objArgs = WScript.Arguments	

set fso = CreateObject("Scripting.FileSystemObject")

If objArgs(0) = 1 Then
	WSH.echo "Creator - Konovalchuk Denis iti-11" & vbCrLf & "option 2 - create a text file with the filenames of folder"
	WSH.echo "option 3 - create zip file with files of a given resolution"
End If

If objArgs(0) = 2 Then
InputFolder = objArgs(1) ' Путь какую папку архивировать 
OutputFolder = objArgs(2) ' Путь куда архивировать

ZipFile = OutputFolder & "\" & objArgs(3)

Set ts = fso.CreateTextFile(ZipFile, True)
ts.Write "PK" & Chr(5) & Chr(6) & String( 18, Chr(0))
ts.Close

Set zip = CreateObject("Shell.Application").NameSpace(ZipFile)

Set sourceItems = CreateObject("Shell.Application").NameSpace(InputFolder).Items

For Each item in sourceItems
	If fso.GetExtensionName(InputFolder & "\" & item) = objArgs(4) Then
		zip.CopyHere(item)
		WScript.Sleep 1000 
	End If
Next

WSH.echo "Done!"
End If

If objArgs(0) = 3 Then
Dim fso, tx, source

Set objArgs = WScript.Arguments

set fso = CreateObject("Scripting.FileSystemObject")

set tx = fso.CreateTextFile(objArgs(2), True)

set source = CreateObject("Shell.Application").NameSpace(objArgs(1)).Items

For Each file in source 
	tx.WriteLine(file)
Next
tx.Close
End If