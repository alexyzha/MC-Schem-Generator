import mcschematic

schem = mcschematic.MCSchematic()
schem.setBlock((0,0,0),"minecraft:stone")

# need to make a key world with rotated stairs, slabs in different orientations, etc.

schem.save("[location]","[name of schem file]",mcschematic.Version.JE_1_19)