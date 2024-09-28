In this project I've implemented an interaction and point of interest system. I've implemented a door with a lockpick minigame as part of the interaction.

WASD to control the player
E to interact to the door (when close enough there will be a prompt)

When in the interaction:
C to cancel the interaction
Left click (or space) to push the pin up
E to set the pin

I have taken from Unreal's CommonUI system to dynamically grab the right image for the keys. I know which keys to display based on what is bound in the actor (in this case the door) using the enhanced input world subsystem, allowing player inputs without a player controller.

The point of interest system works together with the interaction system. I have a component on the player controller which asynchronously checks for any interactable objects in a particular distance and displays the POI if it is. The best interactable actor is picked out of any interactable objects in range by calculating the dot product of the player and the overlapped actor, and then checks if it is also in the interaction range (a closer value than the POI range).

The point of interest widgets are added to a point of interest panel widget that ticks all of them instead of each one ticking individually. I have a custom ProjectWorldToScreenConstrained function which takes into account the aspect ratio when placing the UI (if there are black bars in the editor).

The lockpicking system has a data asset (ULockpickDataAsset) that describes each pin using a pin position. This determines where the correct part of the pin should be to unlock it. The WBP_LockpickInteraction uses this to set up the pins and track what is unlocked. The BP_Door also tracks this.

