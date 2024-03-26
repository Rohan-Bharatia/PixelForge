```dif
!! text in red !!
```

# PixelForge
PixelForge is an open source c++20 game engine with heavy inspiration from Progematic's Hippo game engine
Progematic's hippo game engine GitHub repo: [text](https://github.com/progrematic/hippo)

!!WARNING - (NOT NECESSARY)!!
!!If you want to integrate the CLI into your project, follow these steps to make it easier!!
1. In your command line run:
    ```nano ~/.bash_aliases```
2. Once on the new page, add the line:
    ```alias cli = ./cli```
3. Go back to the main page ('^X' for me), then run:
    ```source nano ~/.bash_aliases```
4. Run the command:
    ```nano ~/.bashrc```
5. Once on the new page, go to the alias definition section of the document (near the bottom)
<<<<<<< HEAD
6. Under the comments, add the line:
    ```if[ ~f ~/.bash_aliases ]; then . ~/.bash_aliases fi```
=======
6. Under the comments, add the lines:
    ```if[ ~f ~/.bash_aliases ]; then . ~/.bash_aliases fi```
>>>>>>> 140420b6908a7ef3cdd85b16124763a917d0132f
