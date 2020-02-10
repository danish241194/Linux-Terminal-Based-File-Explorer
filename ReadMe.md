By: Danish Mukhtar
Roll No: 2018201016
Mtech CSE
 
 Commands : copy , move , rename, delete_file, delete_dir, create_file, create_dir, snapshot, goto, search
 Two ways of running this application
 a. ./file_explorer
 b. ./file_explorer /home/username/...
 
1.Minimum size of terminal required for this application is 80 x 25

2.if there is space in file name or directory name use single quote as 'file name one'.
  if the file conatains single quote as a character (Example : file'name ),use backslash '\' before
  single quote.
***no matter whether there there is space or not ,if file filename contains single quote ,you have to put whole file name in single quotes (Example:  'file\'name')

2.syntax for creating directory or file
	In current directory :	

			create_file filename1 filename2 .

	In any directoy from current directory :
			
			 create_file filename1 folder1/folder2     
	from home
			
			create_file filename1 ~/folder1/folder2

	same goes with directory instead of writing create_file ,you have to write create_dir 

3.syntax for snapshot :       snapshot foldername store_file_name.txt 					(path from current directory)
						or		
			      snapshot ~/fodler1/foder2/foldername foldername store_file_name.txt	(path from home )
	
	To take screenshot of current directory use: snapshot . filename.txt
	To take screenshot of   Home  directory use: snapshot ~/..  filename.txt 			(two dots)

			      
	File will get stored in the directory from where uou are executing application

4. goto command
		
			goto folder1/fodler2/folder3 
				or
			goto /   									 ( to goto home )
				or
			goto ~/folder1/fodler2  		 ( path from home ) 							

 			
5. copy command

	syntax: copy file1 file2 file3 destination_folder
				or
		copy file1 dir1 destination_folder		(path from current directory)
				or
		copy file1 dir1 ~/destinationpath  		 ( path from home )

you can also use commands copy_file , copy_dir to copy files and directories

*destination path and source path must be different
