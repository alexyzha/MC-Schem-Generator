# Minecraft Schematic Generation and Visualization

# Extended documentation:
- __init__( MCStructure class / NONE / filepath_to.schem )
- Calling class constructor with [NONE] will call **_defaultInit**, while a correct filepath will call **_initFromFile**, and a MCStructure will call **_initFromMCStructure**.

- save( save location, schematic name, version, fast saving = false )

- setBlock( tuple(x,y,z), string with blockdata [minecraft std] )

- getBlockStateAt( tuple(x,y,z) ), returns string with blockstate [minecraft std]

- getBlockDataAt( tuple(x,y,z) ), returns string with blockdata [minecraft std]

- placeSchematic( incoming schematic, place position in current )

- placeStructure( incoming MCStructure, place position in current )

- makeCopy(), **returns** MCSchematic that is a copy of the cur

- getSubSchematic( corner coords 1, corner coords 2, recenter = false ), both corner coords are inclusive

- 