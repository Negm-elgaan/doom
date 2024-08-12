#Press Shift+Enter to run the code
givenstring="Lorem ipsum dolor! diam amet, consetetur Lorem magna. sed diam nonumy eirmod tempor. diam et labore? et diam magna. et diam amet."

#Press shift+Enter to run the code
#my sol
class TextAnalyzer1(object):
    
    def __init__ (self, text):
        # remove punctuation
        self.text = text.lower()
        formattedText = text.replace('.','').replace('!','').replace('?','').replace(',','')
        # make text lowercase
        
    def freqAll(self):        
        # split text into words
        x = formattedText.split()
        freqdict = {}
        for i in enumrate(x):
            freqdict[i] = x.count(i)
        return freqdict
        #ibm sol
        # Create dictionary
class TextAnalyzer2(object):
    
    def __init__ (self, text):
        # remove punctuation
        formattedText = text.replace('.','').replace('!','').replace('?','').replace(',','')
        
        # make text lowercase
        formattedText = formattedText.lower()
        
        self.fmtText = formattedText
        
    def freqAll(self):        
        # split text into words
        wordList = self.fmtText.split(' ')
        
        # Create dictionary
        freqMap = {}
        for word in set(wordList): # use set to remove duplicates in list
            freqMap[word] = wordList.count(word)
        
        return freqMap

#Press Shift+Enter to run the code
class TextAnalyzer(object):
    
    def __init__ (self, text):
        # remove punctuation
        formattedText = text.replace('.','').replace('!','').replace('?','').replace(',','')
        
        # make text lowercase
        formattedText = formattedText.lower()
        
        self.fmtText = formattedText
        
    def freqAll(self):        
        # split text into words
        wordList = self.fmtText.split(' ')
        
        # Create dictionary
        freqMap = {}
        for word in set(wordList): # use set to remove duplicates in list
            freqMap[word] = wordList.count(word)
        
        return freqMap
           
    def freqOf(self,word):
        # get frequency map
        freqDict = self.freqAll()
        
        if word in freqDict:
            return freqDict[word]
        else:
            return 0;
