<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
<!--[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![LinkedIn][linkedin-shield]][linkedin-url] -->



<!-- PROJECT LOGO -->
<br />

<!--   <a href="https://github.com/PercyNguyen7/COMP348/Assignments/A1">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a> -->

# 📝🔠Redact and Replacing Word Text Editor
A fun-size project used to redact and replace words in a given text file! 
The user has the option to make changes line by line, including make all possible changes, or no further changes to the programming at any given time.

<!-- USAGE EXAMPLES -->
## 🎯 Functionality
Given any text file, the software reads each line and asks the user if they'd like to edit it 
![image](https://github.com/user-attachments/assets/e1b66903-c4b0-405e-8e54-89bf2d688644)

The software's current 4 mode commands are as followed:

### 1. Redact a word, case considered (RC)
Censoring the specific word by substituting all its instances with a series of asterisks matching the word's length.

> Redacting the word `War` in the string:
> 
> ```text
> War, war never changes. 
> ```
> 
> will result in:
> 
> ```text
> ***, war never changes.
> ```
> Notice the second `war` in the string wasn't changed because it has different casing than `War`.

### 2. Redact a word, case ignored (RI)
Redacting the word and all of its lowercase equivalents by replacing each occurence with consecutive asterisks of the same length as the word.    

> Redacting the word `war` in the string:
> 
> ```text
> War, war never changes. 
> ```
> 
> will result in:
> 
> ```text
> ***, *** never changes.
> ```
> Notice `War` was also changed, as we ignored case.


### 3. Unmask a word , same case (UK)
Unmasking all censored words of same length with the exact word input.    
  
> Unmasking the word `War` in the string:
> 
> ```text
> ***, *** never *******. 
> ```
> 
> will result in:
> 
> ```text
> War, War never *******.
> ```
> Notice `*******` was unchanged, because it has 7 letters while `War` has 3.

### 4. Unmask a word , special case (UM)

Unmasking all censored words of same length with the same word input. However the casing of the replaced word depends on the letter before, the letter after, or the same casing as the word input.

Ex 1: Match case with letter before: 
> Unmasking the word `ar` in string
>
> ```text
> `W**, w** never changes.` 
> ```
>
> will result in:
>
> ```text
> `WAR, war never changes.`
> ```
> The first `**` turned to `AR`, because the letter before it, `W`, is uppercase. Hence `AR` is also uppercase.  
> The second `**` turned to `ar`, because the letter before it, `w`, is lower. Hence `ar` is also lowercase.

Ex 2: No letter before, match case with letter after:
> Unmasking the word `Wa` in string
>
> ```text
> `**R, **r never changes.`
> ```
>
> will result in:
>
> ```text
> `WAR, war never changes.`
> ```
> The first `**` turned to `WA`, because the letter after it, `R`, is uppercase. Hence `WA` is also uppercase.  
> The second `**` turned to `wa`, because the letter before it, `r`, is lower. Hence `wa` is also lowercase.
  
EX 3: No letter before or after, match case with word input   
> Unmasking the word `WaR` in string   
>
> ```text
> `***, *** never changes.`
> ```
>
> will result in:
>
> ```text
> `WaR, WaR never changes.`
> ```
> Both `***` turned to `WaR`, because there is no letter before it or after it. Hence `WaR` has the same case as the input `WaR`.


<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ABOUT THE PROJECT -->
<!--## About The Project

[![Product Name Screen Shot][product-screenshot]](https://example.com) 

Here's a blank template to get started. To avoid retyping too much info, do a search and replace with your text editor for the following: `PercyNguyen7`, `COMP348/Assignments/A1`, , `PercyNguyen`, `project_title`, `project_description`

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With
* [![Svelte][Svelte.dev]][Svelte-url]
* [![Laravel][Laravel.com]][Laravel-url]
* [![Bootstrap][Bootstrap.com]][Bootstrap-url]
* [![JQuery][JQuery.com]][JQuery-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>


* [![Next][Next.js]][Next-url]
* [![React][React.js]][React-url]
* [![Vue][Vue.js]][Vue-url]
* [![Angular][Angular.io]][Angular-url] -->


<!-- GETTING STARTED -->
## ⬇️ Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

### Prerequisites
This project requires to be run on a Linux machine, or run on Ubuntu

### Installation
You may test out the code by either
1. Download the repo's directory via https://download-directory.github.io/ 
   
2. Clone the repo with
   ```sh
   git clone https://github.com/PercyNguyen7/COMP348/Assignments/A1.git
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## 🗃️ File Structure  

### 1. Header Files
- An overview of their C file content
- Declare all functions within their respective C file
   
### 2. C Files  
`kode.c`
- Main file containing the main function.
- Verify number of arguments from command line
- Read text line by line and propose changes if appropriate
  
`fileread.c`    
- Contains all file read and write logic, for instance check_file(), read_line(), write_line()

`ui.c`
- Main file containing the main function.
- Handles user's response (changing line or not) as well as displaying instructions, summary and error messages.

`wordreplace.c`    
- Contains word_replacing functions unique to each mode (RC, RI, UK, UM)
- Contains helper functions ( censor_word, to_lowercase, ...) to avoid overcomplexity in the major functions

## 🛠️ Usage

### Compilation
Once downloaded, compile it and run the following code in your terminal
```sh
  gcc -o kode -Wall kode.c fileread.c wreplace.c ui.c 
   ```

### Running Project
You can run the project with the following command and parameters
`./kode <command> <word> <file>`

| Parameters | Description |
| ------------- | ------------- |
| command| Either RC, RI, UK or UM |
| word | The word you want to redact/unmask in the text file |
| file | The file name |

| Command  | Description |
| ------------- | ------------- |
| RC | Redact Case Sensitive |
| RI | Redact Case Ignored |
| UK | Unmask Keep Case |
| UM | Unmask Special Case |

If you have Valgrind installed, you may also check for memory leak via the following line before running the program:
```sh
    valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./kode <command> <word> <file>
```
<!-- ROADMAP -->
<!-- ## Roadmap

- [ ] Feature 1
- [ ] Feature 2
- [ ] Feature 3
    - [ ] Nested Feature

See the [open issues](https://github.com/PercyNguyen7/COMP348/Assignments/A1/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p> -->



<!-- CONTRIBUTING -->
<!--## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p> -->

<!--### Top contributors:

<a href="https://github.com/PercyNguyen7/COMP348/Assignments/A1/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=PercyNguyen7/COMP348/Assignments/A1" alt="contrib.rocks image" />
</a> -->


<!-- CONTACT -->
## Contact

Project Link: [https://github.com/PercyNguyen7/COMP348/Assignments/A1](https://github.com/PercyNguyen7/COMP348/Assignments/A1)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->
<!-- ## Acknowledgments

* []()
* []()
* []()

<p align="right">(<a href="#readme-top">back to top</a>)</p> -->



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
<!--[contributors-shield]: https://img.shields.io/github/contributors/PercyNguyen7/COMP348/Assignments/A1.svg?style=for-the-badge
[contributors-url]: https://github.com/PercyNguyen7/COMP348/Assignments/A1/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/PercyNguyen7/COMP348/Assignments/A1.svg?style=for-the-badge
[forks-url]: https://github.com/PercyNguyen7/COMP348/Assignments/A1/network/members
[stars-shield]: https://img.shields.io/github/stars/PercyNguyen7/COMP348/Assignments/A1.svg?style=for-the-badge
[stars-url]: https://github.com/PercyNguyen7/COMP348/Assignments/A1/stargazers
[issues-shield]: https://img.shields.io/github/issues/PercyNguyen7/COMP348/Assignments/A1.svg?style=for-the-badge
[issues-url]: https://github.com/PercyNguyen7/COMP348/Assignments/A1/issues
[license-shield]: https://img.shields.io/github/license/PercyNguyen7/COMP348/Assignments/A1.svg?style=for-the-badge
[license-url]: https://github.com/PercyNguyen7/COMP348/Assignments/A1/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/PercyNguyen
[product-screenshot]: images/screenshot.png
[Next.js]: https://img.shields.io/badge/next.js-000000?style=for-the-badge&logo=nextdotjs&logoColor=white
[Next-url]: https://nextjs.org/
[React.js]: https://img.shields.io/badge/React-20232A?style=for-the-badge&logo=react&logoColor=61DAFB
[React-url]: https://reactjs.org/
[Vue.js]: https://img.shields.io/badge/Vue.js-35495E?style=for-the-badge&logo=vuedotjs&logoColor=4FC08D
[Vue-url]: https://vuejs.org/
[Angular.io]: https://img.shields.io/badge/Angular-DD0031?style=for-the-badge&logo=angular&logoColor=white
[Angular-url]: https://angular.io/
[Svelte.dev]: https://img.shields.io/badge/Svelte-4A4A55?style=for-the-badge&logo=svelte&logoColor=FF3E00
[Svelte-url]: https://svelte.dev/
[Laravel.com]: https://img.shields.io/badge/Laravel-FF2D20?style=for-the-badge&logo=laravel&logoColor=white
[Laravel-url]: https://laravel.com
[Bootstrap.com]: https://img.shields.io/badge/Bootstrap-563D7C?style=for-the-badge&logo=bootstrap&logoColor=white
[Bootstrap-url]: https://getbootstrap.com
[JQuery.com]: https://img.shields.io/badge/jQuery-0769AD?style=for-the-badge&logo=jquery&logoColor=white
[JQuery-url]: https://jquery.com -->
