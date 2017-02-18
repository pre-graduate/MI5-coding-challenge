
<img align='right' height='35' width='225' src="code/logo.png" />

# Security Service Coding Challenge

I was looking at various coding challenges online and found this which interested me. The repository just houses the code that outputs the hidden message. It was written in C++ with the use of FreeImage for loading the given image in the challenge. Nothing too complicated but I am quite happy I solved the puzzle.

# Solution (Spoilers !!!)

<img src='code/puzzle.png'/>

Given this image the challenge tells you to find a hidden message. As its size isn’t even and because each row has long sections of the same colour we can assume the message isn’t hidden with each colour representing a one or a zero. So I just counted how many times the next pixel was the same colour in the image. If you treat each number as a ASCII character and print all the values, you realise it’s a list of hexadecimal values separated by a hyphen. Once these hyphens are stripped out it and each hexadecimal value properly converted to an ASCII character you get the hidden message.