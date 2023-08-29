<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="Minishell"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

![image](https://github.com/olxclick/minishell/assets/71394672/30d8c578-3a8f-420f-938c-44ec63c3dc41)

The minishell project is a common programming exercise often assigned in computer science courses and coding bootcamps. It focuses on building a simplified Unix shell, which is a command-line interface that allows users to interact with an operating system by entering and executing commands.

Project Goals:
The primary goals of the minishell project include:

Command Execution: Implementing the ability to interpret and execute basic shell commands entered by the user.

I/O Redirection: Handling input and output redirection, which allows users to redirect command input from files or redirect output to files.

Pipeline Support: Enabling the execution of command pipelines, where the output of one command serves as the input to another.

Built-in Commands: Implementing a set of built-in shell commands (e.g., cd, echo, exit) that are executed within the shell process itself, rather than launching separate processes.

Signal Handling: Managing and responding to signals such as Ctrl+C (SIGINT) and Ctrl+Z (SIGTSTP) to control the behavior of the shell and its running processes.

Environment Variables: Supporting environment variables, allowing users to set, unset, and modify them.

Prompt Display: Displaying a command prompt indicating that the shell is ready to accept user input.

Project Workflow:
The development process for the minishell project typically involves the following steps:

Parsing: Parse the user input to separate commands, arguments, and any special symbols for redirection or pipelines.

Command Execution: Execute the parsed commands by either launching external processes using functions like fork() and exec(), or by handling built-in commands internally.

I/O Redirection: Implement redirection of standard input and output based on user-specified symbols (<, >, >>).

Pipelines: Enable command pipelines by connecting the standard output of one command to the standard input of another.

Signal Handling: Implement signal handlers to catch and respond to signals like SIGINT and SIGTSTP.

Built-in Commands: Implement the behavior of built-in commands within the shell process.

Environment Variables: Manage environment variables and allow users to interact with them.

Prompt: Display a user-friendly prompt to indicate that the shell is ready to receive commands.

<p align="right">(<a href="#Minishell">back to top</a>)</p>

<!-- CONTACT -->
## Contact

João Lázaro - https://www.linkedin.com/in/jlazaro22/ - joaolazaro720@gmail.com

Project Link: [https://github.com/olxclick/minishell](https://github.com/olxclick/minishell)

<p align="right">(<a href="#readme-top">back to top</a>)</p>
