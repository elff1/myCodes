def count_words(string)
  string.gsub!(/\W/, ' ').downcase!
  ans = Hash.new
  string.scan(/(\b\w+\b)/) do |word|
    word = word[0]
    if ans.has_key?(word)
      ans[word] += 1
    else
      ans[word] = 1
    end
  end
  ans
end

puts count_words("Aa,  dd bb. QQ Bb -- cc.")
puts count_words("A man, a plan, a canal -- Panama")
puts count_words "Doo bee doo bee doo"
puts count_words("Madam, I'm Adam!")
