import mcschematic

schem = mcschematic.MCSchematic()
schem.setBlock((0,0,0),"minecraft:stone")
schem.save("[location]","[name of schem file]",mcschematic.Version.JE_1_19)