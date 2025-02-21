# Copy_paste_conpendium
A C++ windows application for storing text, especifically aimed at copy pastas.
## Requirements
[wxWidgets](https://www.wxwidgets.org/) and [nlohmann/json](https://github.com/nlohmann/json)
## TO-DO 
- Add comments to help wtih understanding code <br>
- Add search function. <br>
- Add option for hotkeyng copy pastas. <br>
- Add option to replace matching strings in the app for other strings.<br>
e.g.: "Hello my name is [$NAME]" and user specifies what "name" goes under "[$NAME]"

## How it works
Upon start if no file data is found, in then creates one ("Copy_pasta.JSON") <br>
The window application is launched at mouse position <br>
Button New: creates a new entry data in the JSON File and adds it to the screen.<br>
Button Save: stores the data typed in the text box in the JSON File. <br>
Button Delete: Deletes the selected data, destroys all children(buttons) in the left panel sizer, and repopualtes it from scratch.<br>

