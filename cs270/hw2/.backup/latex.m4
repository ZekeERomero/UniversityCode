% helloTex.m4  
%
%   An m4 file to package source files for submission.
%  After using m4 on this file, a single file will
%  be generated with the contents of the included files
%  (hello.h, testHello.c, and hello.c).
%
%  To generate a file for typesetting:
%
%   m4 helloTex.m4 > NameSrc.tex
%
%  This resulting file can be typeset if desired.

\documentclass[12pt]{article}

%\usepackage[fancybox]
%\usepackage{color}  % old
\usepackage[usenames]{color}
\definecolor{light-gray}{gray}{0.65}

\begin{document}

\section{Introduction}

My introduction...

\pagebreak

\section{Output}

Sample output...

\pagebreak

\section{Program Log}

April 6: Demo!

\pagebreak

\section{Source Code}

%  Header file(s)

\subsection{lineNum.sh}

\begin{verbatim}
include(`lineNum.sh')
\end{verbatim}

\pagebreak

%  main file 

\subsection{fileName.sh}

\begin{verbatim}
include(`fileName.sh')
\end{verbatim}

\pagebreak

%  auxiliary file(s)
\subsection{backup.sh}

\begin{verbatim}
include(`backup.sh')
\end{verbatim}

\end{document}

