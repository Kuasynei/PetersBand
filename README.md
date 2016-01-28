# Symphony of Shadows
---
## Managing your Branch
- **DO NOT** edit the .gitignore or README.
- **DO NOT** make pulls into other branches, NOR UE4Develop, NOR master, without talking to the team first. 

- **DO** create a "Feature Branch" when you're implementing a new feature.
- **DO** talk to the team before attempting to merge & pull your feature into the UE4 develop branch.

We are using UE4 version 4.9. Make sure to check the naming convention doc [**on the drive**](https://docs.google.com/a/rcc.yorkvilleu.ca/document/d/1IyFd9RRYVlWAZwuV6bXzYpwrdLZs8mMJb_fwcU5mRpc/edit?usp=sharing) when making commits and new feature branches.


## How to rebuild your UProject
1. Right-Click on "projectnamehere.uproject" (Unreal Engine Project File).

2. Make sure the version is 4.9 by clicking on "Switch Enreal Engine version..."

3. When that finishes Right-Click on the .uproject again and select "Generate Visual Studio project files".

4. When that finishes, open "projectnamehere.sln" (Microsoft Visual Studio Solution). 

5. In your "Solution Explorer" (A window in Visual Studio), there should be two folders: Engine &    Games. 

6. Open the "Games" folder and there will be the project file. 

7. Right-click on the project file

8. Click "Properties" in the drop-down

9. Under "Configuration Properties" click on "VC++ Directories"

10. If "Include Directories", "Reference Directories", "Library Directories" and "Library WinRT Directories" have empty fields, click on the fields and open the drop-down; otherwise skip to step 12.

11. Click "inherit from parent or project defaults" for each field.

12. Close that window, then hit F5 to start up UE4. 

13. From now on you can just open "projectnamehere.sln" (Microsoft Visual Studio Solution) and hit F5 to start UE4.



## How to Commit
Put your UE4 project folder in your github folder. If you need to delete project files to reduce size, your can delete everything EXCEPT THE FOLLOWING:

* Config (Folder)
* Content (Folder)
* Source (Folder)
* projectnamehere.uproject

*!!DO NOT DELETE .gitignore OR THE README!!*


## Troubleshooting

Q: When I open "projectnamehere.sln" (Microsoft Visual Studio Solution), the files/folders are weird, 
   and I can't move to the next step.
A: If you're not on school computers try this:

1. While you are running the game through Visual Studio check the bottom left of the window, and make sure you are in the "Solution Explorer" tab.

2. Click on the "Solution Explorer" tab  if you haven't already. If your folder structure is stlll not fixed proceed onto the next set of steps.

1. Close any Visual Studio windows you have open.

2. Delete "projectnamehere.sln" (Microsoft Visual Studio Solution) if it exists in the project folder.

3. When that finishes Right-Click on the .uproject again and select "Generate Visual Studio project files".

4. Open "projectnamehere.uproject" (Unreal Engine Project File).

5. Click File (Top left), then "Refresh Visual Studio Project".

6. Open ANY C++ script (not a blueprint).

7. If the file structure is not fixed by this point, close UE4.

8. Open "projectnamehere.sln" (Microsoft Visual Studio Solution) and hit F5 to start UE4.

9. Open ANY C++ script (not a blueprint)(again). It should be fixed at this point.