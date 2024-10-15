import mcschematic

WIDTH = 60
LENGTH = 60
FILENAME = 'output.txt'

schem = mcschematic.MCSchematic()

with open(FILENAME,'r') as file:
    for i in range(WIDTH):
        for j in range(LENGTH):
            line = file.readline()
            val = int(line.strip())
            for k in range(val):
                schem.setBlock((i,k,j),"minecraft:stone")

schem.save("test_schem","test1",mcschematic.Version.JE_1_19)
