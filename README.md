## DesiredSizeBox UMG Panel for Unreal Engine 5

This is a simple modification of SizeBox that is already present in Unreal Engine 5, which allows users to modify the desired size reported by the panel's child. Regular SizeBox allows users to override desired height and width to a specific value, but sometimes this is not what the user wants. One such case is when you'd like to create an animation where the widget fades in onto the screen and expands its height from 0% to 100%.

An example of such a widget could be a context menu that appears after you right-click an item in your inventory:

![Context Menu](https://user-images.githubusercontent.com/38283075/162013372-5c07d367-f014-4744-ae50-c78de04ed3f4.gif)

DesiredSizeBox has "Height Factor" and "Width Factor" properties which are multiplied by its child's desired height and width. You can keyframe these properties in animations to easily create widget height/width expansion animations from 0% to 100%.

![Details](https://user-images.githubusercontent.com/38283075/162013396-2a177c97-1c3c-4a1f-8980-0edddb8d93ca.png)

## How to use?

Simply copy .h and .cpp files to your Source directory and build your project. You should see DesiredSizeBox in the Palette while you use UMG editor.

![Palette](https://user-images.githubusercontent.com/38283075/162013425-7c71e6e0-b531-4898-a5a6-dfd37cb5ac25.png)
