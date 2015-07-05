#readStringFromFile Function

The `readStringFromFile_noHeader.c` is an example which doesn't use, well headers. Mostly because I wrote this in Dev-C++ and I couldn't figure out how to. (Yes I know. I have VS.)

The `readStringFromFile.c` and `readStringFromFile.h`, are there for you to use if you decide to use the header thing. But I might have missed something from either the .c or .h file. I'm not sure, I think it should work. Not sure. Sorry about that.

***

##Description:
>Takes in an input file and scans a collection of whitespace characters into a fixed character array.
>Since it uses the FILE Pointer, it can be used at any point to extract words (or string of alpha
>characters ). If it encounters an End Of File before it begins to extract a word, it returns a 
>NULL character array and sets the checker (passed in by reference) to the End Of File int.
	
	
##Background:
>The code was written to replace my older 'extractWord' function which took in the same parameters
>but ultimately was unable to complete the event that i wanted it to. It, for some reason, was only
>able to scan in 40-50 words before crashing. After almost an entire day of debugging, I came to 
>the conclusion that the error was caused by a segfault (probably), but it was certainly caused
>by the malloc and realloc functions.
	
>As A result I rewrote the function to be slightly safer, in terms of error checking and in terms
>of memory usage. With this new code I was able to quickly and effectively read in 5000+ words in
>less than 0.5 seconds. Which I'm sure isn't anything big, but considering that my code before
>fell apart by the fiftyth word, I consider this a big improvement.
	
	
##Limitations:
>As noted above, this probably isn't the fastest way to read in words and data from an input file
>but it was clean enough for the assignment I needed it for.
	
>Memory Usage: Its quite inefficient as the temporary character string doubles every time it needs to.
>So it starts at 1, then it goes to 2, then 4, 8, etc. Hopefully, I did this so you would call 
>realloc only a small number of times. Now that I think of it, I could've just called it once or twice
>if i started the size at something like 10 or 20. You can fix that if you want.
	
>Speed: 5000-5500 in roughtly 0.5 seconds doesn't sound like much. I don't really know, I never paid attention
>in the classes that taught these things. I should really do that.
	
>Actual Code: As i noted, this probably isn't the best way to do the things  I did. I'm sure there's a 
>faster library out there for something like this.

###NB:
>I wrote this because that malloc error was pissing me off and it took me way to f-ing long to
>debug and figure out that was the problem. So Moral of the stor: Don't be me.

###Disclaimer
I don't know what the F I'm doing.
