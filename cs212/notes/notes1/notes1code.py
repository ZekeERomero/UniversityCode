#!/usr/bin/env python3
import sys
import notes1 as mc
from argparse import ArgumentParser

def main():
	parser = ArgumentParser()
	parser.add_argument("-e", "--encode", dest="encode", default=False,
			action="store_true", help="encode the message. Default is decode")
	parser.add_argument("keyword", type=str, help="keyword or phrase for code")
	args = parser.parse_args()
	
	removeThese = " .,:;?'!\n"
	if (args.encode):
		text = sys.stdin.read()
		text = text.translate("".maketrans(removeThese, len(removeThese)*"."))
		text = text.replace(".", "")
		text = text.lower()
		print(mc.encaesar(args.keyword, text))
	else:
		text = sys.stdin.read()
		#print(mc.	
	#print(args)#.encode)
main()
