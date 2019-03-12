# a2-model-150070011_150020069
a2-model-150070011_150020069 created by GitHub Classroom

youtube link for the final video - 
https://www.youtube.com/watch?v=ow5TPxBHUm4&feature=youtu.be

The room has following Furnitures -
A Table, A Music Box on Top of it with 2 characters - Iron Man and Captain America. A chair, A bed, A mattress on the bed, A Lamp, A tubelight, A Cupboard, A door, A window with the outside view, etc.

By default the current node is the Lower Torso of Captain America
Current Node can be rotated by using the rotation controls mentioned below

Current Node Rotation Controls

| 		KEY 	| Rotation Effect  |
| ------------- | ------------- |
| Left Arrow Key| Decrease Ry |
| Right Arrow Key| Increase Ry |
| Up Arrow Key| Decrease Rx |
| Down Arrow Key| Increase Rx |
| Page Up | Decrease Rz) |
| Page Down| Increase Rz |

Camera Position Controls

| 		KEY 	| Change in Camera Rotation  |
| ------------- | ------------- |
| R| Decrease Cy by 0.25|
| T| Increase Cy by 0.25|
| Y| Decrease Cx by 0.25|
| U| Increase Cy by 0.25|
| G| Decrease Cz by 0.25|
| H| Increase Cz by 0.25|

Pressing a Key Changes the Current Node which can then be rotated Using Arrow Keys

Controls for the Music Box 

| 		KEY 	| Action  |
| ------------- | ------------- |
| 1| Music Box Opens |
| 2| Music Box Closes |

Controls for the Captain America

| 		KEY 	| New Current Node  |
| ------------- | ------------- |
| 3| Lower Torso of Iron Man (Root Node) |
| 4| Upper Torso |
| 5| Left Shoulder |
| 6| Right Shoulde |
| 7| Left Hip |
| 8| Right Hip |
| Z| Move Captain America Forward |
| X| Move Captain America Backward |

Controls for the Iron Man

| 		KEY 	| New Current Node  |
| ------------- | ------------- |
| 9| Iron Man Torso (Root Node) |
| 0| Iron man face |
| -| Left Shoulder |
| +| Right Shoulder |
| C| Move Captain America Forward |
| F| Move Captain America Backward |

Lighting Controls
There are 2 lights in the room. One tubelight and one lamp.

| 		KEY 	| Action  |
| ------------- | ------------- |
| V| Toggle Tubelight |
| B| Toggle Lamp |

# Beizer Curve For Camera Movement
Click the points where you want the camera to move. A sphere will be formed at the actual clicked points in 3D.
Press the key I after you are done. A beizer curve will show up on the path formed. Press the key O to move camera on the beizer curve. 

# Recording KeyFrames
Do the character animation. Move the character parts as desired. Press the key L to store the keyframes. Once you are done storing all the keyframes, press M to start the whole animation. 

# References
1) https://www.tomdalling.com/blog/modern-opengl/06-diffuse-point-lighting/
2) https://www.tomdalling.com/blog/modern-opengl/07-more-lighting-ambient-specular-attenuation-gamma/
3) Keyframe Dumping using ofstream - http://www.cplusplus.com/reference/fstream/ofstream/ofstream/
