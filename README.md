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

<h2>Project Goals:</h2>
<br>
The primary goals of the minishell project include:

<b>Command Execution:</b> Implementing the ability to interpret and execute basic shell commands entered by the user.

<b>I/O Redirection:</b> Handling input and output redirection, which allows users to redirect command input from files or redirect output to files.

<b>Pipeline Support:</b> Enabling the execution of command pipelines, where the output of one command serves as the input to another.

<b>Built-in Commands:</b> Implementing a set of built-in shell commands (e.g., cd, echo, exit) that are executed within the shell process itself, rather than launching separate processes.

<b>Signal Handling:</b> Managing and responding to signals such as Ctrl+C (SIGINT) and Ctrl+Z (SIGTSTP) to control the behavior of the shell and its running processes.

<b>Environment Variables:</b> Supporting environment variables, allowing users to set, unset, and modify them.

<b>Prompt Display:</b> Displaying a command prompt indicating that the shell is ready to accept user input.

<h2>Project Workflow:</h2>
The development process for the minishell project typically involves the following steps:

<b>Parsing:</b> Parse the user input to separate commands, arguments, and any special symbols for redirection or pipelines.

<b>Command Execution:/<b> Execute the parsed commands by either launching external processes using functions like fork() and exec(), or by handling built-in commands internally.

<b>I/O Redirection:</b> Implement redirection of standard input and output based on user-specified symbols (<, >, >>).

<b>Pipelines:</b> Enable command pipelines by connecting the standard output of one command to the standard input of another.

<b>Built-in Commands:</b> Implement the behavior of built-in commands within the shell process.

<b>Environment Variables:</b> Manage environment variables and allow users to interact with them.

<b>Prompt:</b> Display a user-friendly prompt to indicate that the shell is ready to receive commands.

<p align="right">(<a href="#Minishell">back to top</a>)</p>

<!-- CONTACT -->
## Contact

João Lázaro - https://www.linkedin.com/in/jlazaro22/ - joaolazaro720@gmail.com

Project Link: [https://github.com/olxclick/minishell](https://github.com/olxclick/minishell)

<p align="right">(<a href="#readme-top">back to top</a>)</p>
