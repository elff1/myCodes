def combine_anagrams(words)
  models = Array.new
  groups = Array.new
  words.each do |word|
    newModel = word.downcase.split(//).sort.join
    flag = false
    for i in (0..models.length - 1)
      #puts i
      if newModel == models[i]
        groups[i].push(word)
        flag = true
        break
      end
    end
    next if flag
    models.push(newModel)
    groups.push(Array[word])
  end
  groups
end