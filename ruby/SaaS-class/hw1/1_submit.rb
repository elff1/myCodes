def palindrome?(string)
  string.downcase!.gsub!(/\W/, '')
  string == string.reverse
end

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