def combine_anagrams(words)
  models = Array.new
  groups = Array.new
  words.each do |word|
    newModel = word.downcase.split(//).sort.join
    #puts "<<#{newModel}>>"
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
  #puts
  #models.each {|model| print "#{model} "}
  #print "\n"
  #puts
  groups
end

words = ['cars', 'for', 'potatoes', 'racs', 'four','scar', 'creams', 'scream']
#puts words
combine_anagrams(words).each do |group|
  group.each {|word| print "#{word} "}
  print "\n"
end
