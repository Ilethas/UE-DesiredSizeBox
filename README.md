## DesiredSizeBox UMG Panel for Unreal Engine 4

This is a simple modification of SizeBox that is already present in UE4, which allows users to modify the desired size reported by the panel's child. Regular SizeBox allows users to override desired height and width to a specific value, but sometimes this is not what the user wants. One such case is when you'd like to create an animation where the widget fades in onto the screen and expands its height from 0% to 100%.

An example of such a widget could be a context menu that appears after you right-click an item in your inventory:

![Context Menu](https://user-images.githubusercontent.com/38283075/149150098-19702d9f-4e18-45a8-8ce5-ef51006910bd.gif)

DesiredSizeBox has "Height Factor" and "Width Factor" properties which are multiplied by its child's desired height and width. You can keyframe these properties in animations to easily create widget height/width expansion animations from 0% to 100%.

![Details](https://user-images.githubusercontent.com/38283075/149151757-24c4990c-0d6d-4330-a0f3-733469fd1a07.png)

## How to use?

Simply copy .h and .cpp files to your Source directory and build your project. You should see DesiredSizeBox in the Palette while you use UMG editor.

![Palette](https://user-images.githubusercontent.com/38283075/149152616-f53a02d5-045e-4cac-bc51-81a1bc8c5e43.png)
