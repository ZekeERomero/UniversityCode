#!/usr/bin/env python3
from turtle import (Screen, Turtle)
screen = Screen()

def stopit():
	print("Exitting")
	quit()

def openDraw():
	"""open a canvas to draw on"""
	height = 1000
	width = 1000
	screen.setup(width, height)
	screen.bgcolor("black")
	screen.setworldcoordinates(0, 0, width, height)
	screen.onclick(stopit)

	t.Turtle()
	t.pensize(3)
	t.speed(0)
	t.pencolor("red")
	#t.hideturtle()

	return t

def runDraw(t, instructions):
	"""do the drawing using character based instructions"""
	size = 100
	angle = 90

	addr = 0
	while addr < len(instructions)
		instr = instructions[addr]
		if instr == 'F':
			t.forward(size)
		elif instr == '+':
			t.left(angle)
		addr += 1
	
	

#"F+F+F+F" -> square
#F = Forward
#+ = Turn 90 degrees

def main():
	t = openDraw()
	#t.forward(10)
	#t.right(10)
	#t.clear(10)
	runDraw(t, "")

main()
