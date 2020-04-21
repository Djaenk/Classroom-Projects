from hashlib import sha256
from multiprocessing import Pool
from itertools import permutations
import time

def read_hashes(hash_file):
	hashes = dict()
	with open(hash_file, 'r') as hashfile:
		lines = hashfile.readlines()
	for hash in lines:
		hashes[hash.rstrip()] = ""
	return hashes

def print_hashes(hashes):
	for hash, password in hashes.items():
		print(f'{hash}:{password}')

def write_hashes(hash_file, hashes):
	with open(hash_file, 'w+') as hashfile:
		for hash, password in hashes.items():
			hashfile.write(hash)
			hashfile.write(":")
			hashfile.write(password)
			hashfile.write("\n")

def hash_password(password):
	return sha256(password.strip().encode()).hexdigest()

def verify_password(password, hashes):
	hash = sha256(password.strip().encode()).hexdigest()
	if hash in hashes:
		hashes[hash] = password.strip()

def dictionary_attack(hashes, dictionary_file):
	with open(dictionary_file, 'r', encoding="latin-1") as dictionary:
		for line in dictionary:
			verify_password(line, hashes)
		# with Pool() as pool:
		# 	for line in dictionary:
		# 		pool.apply_async(verify_password, (line, hashes))

def brute_force_attack(hashes, length):
	for char_tuple in permutations(characters, length):
		verify_password("".join(char_tuple), hashes)

def mutated_dictionary_attack(hashes, dictionary_file):
	with open(dictionary_file, 'r', encoding="latin-1") as dictionary:
		for line in dictionary:
			for variant in get_variations(line, 0):
				if hash_password(variant) in hashes:
					hashes[hash_password(variant)] = variant

def get_variations(password, index):
	variations = []
	if index < len(password):
		try:
			for char_alternative in character_alternatives[password[index]]:
				variation = password[:index] + char_alternative + password[index + 1:]
				variations.append(variation)
				variations.extend(get_variations(variation, index + 1))
			variations.extend(get_variations(password, index + 1))
		except:
			pass
	return variations

characters = "`1234567890-=~!@#$%^&*()_+qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM,./;\'[]\<>?:\"{}| "

character_alternatives = {
	'a': ['A', '@', '4'],
	'b': ['C', '8', '6'],
	'c': ['C', '<', '{', '[', '('],
	'd': ['D', '0'],
	'e': ['E', '3'],
	'f': ['F'],
	'g': ['G', '[', '-', '6', '9'],
	'h': ['H', '4'],
	'i': ['I', '1', '!', '|', '9'],
	'j': ['J', '7', '9'],
	'k': ['K'],
	'l': ['L', '1', '|'],
	'm': ['M'],
	'n': ['N'],
	'o': ['O', '0'],
	'p': ['P'],
	'q': ['Q', '9', '0'],
	'r': ['R', '2'],
	's': ['S', '5', '$'],
	't': ['T', '7', '+'],
	'u': ['U'],
	'v': ['V'],
	'w': ['W'],
	'x': ['X', '%', '*', '8'],
	'y': ['Y'],
	'z': ['Z', '2', '5']
}

if __name__ == "__main__":
	start_time = time.time()
	hashes = read_hashes("hashes.txt")
	dictionary_attack(hashes, "realhuman_phill.txt")
	dictionary_attack(hashes, "rockyou.txt")
	for i in range(1,5):
		brute_force_attack(hashes, i)
	write_hashes("passwords.txt", hashes)
	print(f"{time.time() - start_time}")
	pass