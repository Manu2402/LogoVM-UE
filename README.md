# LogoVM-UE

## Overview
- A simple Unreal Engine 5 plugin that deals with a virtual execution/interpretation environment (<b>Virtual Machine</b>) for programs written using the <i>LOGO programming language</i> <br>
- LOGO is a very simple interpreted language, which in its most minimal form provides basic commands for drawing on a canvas using a “brush” (turtle) <br>
- For more information about the LOGO language, visit: https://en.wikipedia.org/wiki/Logo_(programming_language)

## Setup
- Download this project and unzip it (beware this repo includes an example project and the plugin)
- Copy or move it into "Plugins" folder in your project or your engine, if not present you must create it (the name must be "Plugins")
- Rebuild your project
- Open your project and enable "LogoVM" plugin check if this plugin is recognized (under Edit/Plugins toolbar menu)
- <b>WARNING</b>: Do not copy/move/rename/delete none of the assets in the plugin content except "LogoTest" (Level) and "Example" (Texture)

## Primary features
- You can put “LOGO path/to/file.logo” in the console to execute LOGO commands (Editor + Runtime)
- You can drag-n-drop ".logo" files in order to generate a texture (with optional and custom resampling) from them (Editor)
- Blueprint Function Library that adds nodes to execute LOGO programs (both single commands and "path/to/logo" file) (Runtime)

## Secondary features
- You can customize the size of the canvas where you draw your beautiful paints by a dedicated Data Asset (Editor)
- You can customize the texture resolution before generate it, in order to resample with a greater quality your paints by a dedicated Data Asset (Editor)

## Available commands
- <b>fd</b> "steps" (FORWARD)
- <b>bk</b> "steps" (BACKWARD)
- <b>rt</b> "angle" (RIGHT TURN)
- <b>lt</b> "angle" (LEFT TURN)
- <b>ct</b> (CENTER TURTLE)
- <b>cs</b> (CLEAR SCREEN)
- <b>pu</b> (PEN UP)
- pd</b> (PEN DOWN)
- <b>pc</b> "color id" (PEN COLOR)
- <b>repeat</b> "cycles" [...] (REPEAT)

### Available colors
- 0 = White
- 1 = Black
- 2 = Red
- 3 = Blue
- 4 = Green
- 5 = Yellow
- 6 = Cyan
- 7 = Magenta
- 8 = Orange

## Screenshots and code example
![2](https://github.com/user-attachments/assets/382fd359-90d8-4ffc-bf55-9e8b00e84a71)<br><br>

LOGO program about this example:

```
cs        
ct        
pc 3      
pd        

repeat 4 
[
  fd 10
  rt 90
]

pu 
bk 5
lt 90
fd 5
rt 90
pd      

pc 7

repeat 4 
[
  fd 8
  rt 90
]
```

![1](https://github.com/user-attachments/assets/b71ce2dd-2e25-4833-acf9-8d3fdde68e22)

## Next steps
- Add the minimum subset of commands in order to write and interpret a "Turing complete" version of LOGO programming language:
   - make “var value (make “n 3) | :var (:n) -> Get/Set Integer Variables
   - print :var (print :n) | print 3 -> Print Integers And Integer Variables
   - if (if :n > 5 [...]), ifelse (ifelse :n mod 3 = 0 [...][...]) -> Between Integers and Integer Variables
   - to func_name … end -> Procedures
   - to func_name :param \n output … end  -> Functions with Parameters and Return
- Add some operands:
   - "+"
   - "-"
   - "*"
   - "/"
   - "mod"
   - "="
   - "<(=)"
   - ">(=)"
   - ";" (comments) 
- Merge all the tiles into a single (procedural) mesh
