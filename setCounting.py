def countSets(array):
    numSets = 0
    for x in range(0, len(array) - 2):
        for y in range(x + 1, len(array) - 1):
            for z in range(y+1, len(array)):
                if(array[x]^array[y] == array[z]):
                    numSets+=1
    return(numSets)


#get dimension
try:
    dim = int(input("What dimension do you want? "))
    print("The dimension is:", dim)
except ValueError:
    print("Invalid input. Please enter an integer.")

numCards = 2**dim - 1 #total possible cards

#get number of cards
pickNum = numCards + 1
while(pickNum > numCards):
    try:
        pickNum = int(input("How many cards? "))
        if(pickNum <= numCards):
            print("Collections of size: ", pickNum)
        else:
            print("Too many cards! Max is:", numCards)
    except ValueError:
        print("Invalid input. Please enter an integer.")


    
numCollections = 0 #counts possible collections
cards = [] #array of (pickNum) cards
maxs = [] #last possible collection of cards
setCounts = [] #number of sets in each possible collection

#generate the starting cards and maxs array
#cards look like [1, 2, 3...]
#maxs look like [8, 9, 10...] (depends on size)
for num in range(1, pickNum+1):
    cards.append(num)
    maxs.append(numCards - (pickNum - num))
print("\n")
print("Starting at:", cards)
print("Ending at:", maxs)

#cycle through all possible collections of (pickNum) cards, counting the number of sets in each
while(cards[0] <= maxs[0]):
    setCounts.append(countSets(cards))
    numCollections +=1 
    
    #if last card isn't maxed out, increase it
    #otherwise, find the next collection
    if(cards[pickNum-1] < maxs[pickNum-1]):
        cards[pickNum-1] += 1
    elif(cards[pickNum-1 == maxs[pickNum-1]]):
        #find the last card that isn't maxed out
        index = pickNum - 1
        while(cards[index] == maxs[index]):
            index-=1
            if(index == -1):
                break
            
        if(index == -1):
            index+=1 #just to not go out of bounds
        cards[index] +=1 #increase the last card not maxed out
        while(index < pickNum-1):
            cards[index+1] = cards[index] + 1
            index +=1
            #"resets" all the cards after the index
            #eg, [1, 2, 14, 15] -> [1, 3, 4, 5]
    else:
        print("last card went out of range")
        

maxSetCount = max(setCounts) #highest number of sets in any possible collection
print("\n")
print("Max Set Count:", maxSetCount)
print("Number of possible collections:", numCollections)

setData = []
for x in range(0, maxSetCount+1):
    setData.append(0)

for x in setCounts:
    setData[x] += 1

print("\n")
print("--Set Data--")
print("#Sets  Frequency")
for x in range(0, maxSetCount+1):
    print(x, "\t"," ", setData[x])
 

    
