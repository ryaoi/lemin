#!/usr/bin/env python

import sys
import os
import shutil
from copy import deepcopy
from subprocess import call

def main():
	if os.path.exists("./visu/output"):
		shutil.rmtree('./visu/output')	
	os.makedirs("./visu/output")
	got_ants, room_def, start,end = 0,0,0,0
	got = ""
	step = 1
	end_room = ""
	shader = "basic"
	graph = {"nodes": {}, "edges": []}
	for line in sys.stdin:
		if line != "Error\n":
			if line == "\n":
				break 
			got += line
			line = line.strip()
			if (not got_ants and line[0] != '#'):
				got_ants = 1
			elif '-' in line:
				room_def = 1
				tab = line.split('-')
				graph['edges'].append({"source": tab[0], "target": tab[1]})
			elif (got_ants and not room_def and line[0] != '#'):
				tab = line.split()
				if start:
					graph['nodes'][tab[0]] = {'color': 0xffaaaa, 'size':2.0}
					start = 0
				elif end:
					graph['nodes'][tab[0]] = {'color': 0x4B1657, 'size':2.0}
					end_room = tab[0]
					end = 0
				else:
					graph['nodes'][tab[0]] = {}
			elif (line == "##start"):
				start = 1
			elif (line == "##end"):
				end = 1
			elif (line.startswith("#shader:")):
				line = line[8:]
				if (line == "basic" or line == "phong" or line == "lambert" or line == "toom"):
					shader = line
		elif not line:
			print "Bad input"
			exit()
	print(got)
	#print the result to a file

	with open('./visu/output/map.py', 'w') as f:
		sys.stdout = f
		print "import jgraph"
		sys.stdout.write('graph = ')
		print (graph)
		print "jgraph.draw(graph, z=200, size=(800, 600), directed= False, shader= \"" + shader + "\")"
	sys.stdout = sys.__stdout__
	print "[*]Created map.py!"

	for line in sys.stdin:
		if (line.startswith("[turn")):
			print("Launch this program without verbose mode!")
			exit()
		copy = deepcopy(graph)
		ssplit = line.strip().split()
		for word in ssplit:
			room = word.split('-')
			if (end_room != room[1]):
				copy['nodes'][room[1]] = {'color': 0xA21F4D, 'size':1.0}
		with open('./visu/output/step' + str(step) + '.py', 'w') as f:
			sys.stdout = f
			print "import jgraph"
			sys.stdout.write('graph = ')
			print (copy)
			print "jgraph.draw(graph, z=200, size=(800, 600), directed= False, shader= \"" + shader + "\")"
			sys.stdout = sys.__stdout__
			print "[*]Created step" + str(step) + ".py!"
			step += 1

	with open('./visu/output/cmd.txt', 'w') as f:
		sys.stdout = f
		print "%run map.py"
		i = 1
		while i < step: 
			print "%run step" + str(i) + ".py"
			i += 1
		sys.stdout = sys.__stdout__
	
	print ("\n[copy and paste this to the notebook!]")
	call(["cat", "./visu/output/cmd.txt"])

if __name__ == '__main__':
	main()
