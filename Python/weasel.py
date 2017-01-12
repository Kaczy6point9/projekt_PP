import random
import string

def randomString(size):
  return ''.join(random.choice(string.ascii_uppercase + ' ') for _ in range(size)) 

def stringmutation(sentence):
  new_senetence = list(sentence)
  index = random.randrange(len(sentence))
  new_senetence[index] = random.choice(string.ascii_uppercase + ' ')
  return ''.join(new_senetence)

def sen_score(score_sentence, sentences):
  score = len(score_sentence)
  max_score = 0
  best_sentence = sentences[0]

  for x in range(len(sentences)):
    sentence_score = 0
    pom1 = sentences[x]
    if pom1 == score_sentence:
      return pom1
    else:
      for y in range(len(pom1)):
        if pom1[y] == score_sentence[y]:
          sentence_score += 1
        if sentence_score > max_score:
          best_sentence = pom1
  print(sentence_score)
  print(best_sentence)
  return best_sentence


def weasel(score, sentence):

  sentences = []	
  for _ in range(100):
    sentences.append(sentence)
	
  mutations = []

  for x in range(len(sentences)):
    mutations.append(stringmutation(sentences[x]))
  best_sentence = sen_score(score, mutations)
  gen = 1
  while best_sentence != score:
    
    del sentences[:]
    del mutations[:]
    for _ in range(100):
      sentences.append(best_sentence)

    for x in range(len(sentences)):
      mutations.append(stringmutation(sentences[x]))
    best_sentence = sen_score(score, mutations)
    gen += 1
    print(gen)
  

  return best_sentence 

score = "METHINKS IT IS LIKE A WEASEL"
sentence = randomString(len(score))
print(weasel(score, sentence))