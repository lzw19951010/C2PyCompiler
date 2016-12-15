next = [0] * (80)
next[0] = -999
def get_next(T,next):
	k = -1
	j = 0
	l = len(T)
	next[j] = k
	while j<l:
		if (k==-1 or T[j]==T[k]):
			k += 1
			j += 1
			next[j] = k
		else:
			k = next[k]
def index_KMP(S,T,pos):
	i = pos
	j = 0
	while (i<len(S) and j<len(T)):
		if (j==-1 or S[i]==T[j]):
			i += 1
			j += 1
		else:
			j = next[j]
	if len(T)==j:
		return i-len(T)
	else:
		return -1
def main():
	s = [0] * (80)
	t = [0] * (80)
	s = input()
	t = input()
	pos = 0
	get_next(t,next)
	index = index_KMP(s,t,pos)
	print(index)

if __name__ == '__main__':
	main()

