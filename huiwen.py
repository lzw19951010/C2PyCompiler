def main():
	ans = 1
	i = 0
	j = 0
	k = 0
	str = [0] * (100)
	str = input()
	i = len(str)
	j = i+1
	j = j/2
	k = 0
	while k<j:
		if str[k]!=str[i-1-k]:
			ans = 0
			break
		k += 1
	print(ans)
	return 0

if __name__ == '__main__':
	main()
