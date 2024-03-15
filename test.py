

class UhrenScriptHelperFunctions:
	result     = None
	minArray   = [0,0,0,0,0,0]
	valueArray = [1,2,4,8,16,32]

	def __init__(self, userIO=30):
		pass

	def computeBinary(self, userIO=30, mode=5) -> None:
		#print(f'[+] Starting {UhrenScriptHelperFunctions.computeBinary.__name__}...')
		arrayField = 0
		(counter = 5) if (mode == 0) else (counter = 4) 
		self.result = userIO
		while(self.counter >= 0):
			if(self.result - self.valueArray[counter] >= 0):
				self.result -= self.valueArray[counter]
				self.minArray[arrayField] = 1
			else:
				self.minArray[arrayField] = 0
			counter -= 1
		#print(f'[=] {userIO} in Binary is {self.minArray}')

	def countingMinutes(self) -> None:
		print(f'[+] Starting {UhrenScriptHelperFunctions.countingMinutes.__name__}...')
		for i in range(1, 61):
			print(f'[+] Minute {i}...')
			self.computeBinary(i)
			print(f'[=] in Binary {self.minArray}...')


if __name__ == '__main__':
	instance = UhrenScriptHelperFunctions()
	#instance.computeBinary()
	instance.countingMinutes()
