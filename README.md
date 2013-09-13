slice
=====

This C++ code reads a plain text (no html) from standard input and writes to standard output a javascript that outputs that same text.

> g++ -g javascripter.c
> ./a.exe < testme.in > testme.html

then open .../testme.html in your browser. A popup window will appear before the message is displayed.

The objective is not to prevent anyone from snooping on one single email message , nor even to conceal the message as in cryptography, but to make it too expensive to snoop on a large enough volume of emails.

Running the output javascript takes time and space linear in the message length n.
My goal here is to make snooping on p messages of length n take O(p*n*n) time or space unless one executes the p javascripts.
As you know, big O notation applies to n>>1 or p>>1.

This code is a proof of concept, it is not secure, it is not bullet proof, and it will likely produce garbage on html input.

As usual: I take no responsability for any use or abuse of this software or its derivatives. What comes free comes with no waranty.

Send comments and suggestions to malardj@acm.org.

Tinker and Enjoy!

Joel M. Malard
date: 09/12/2013
