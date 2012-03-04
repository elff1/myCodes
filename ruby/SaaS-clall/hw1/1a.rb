def palindrome?(string)
  string.downcase!.gsub!(/\W/, '')
  string == string.reverse
end

puts palindrome?("A man, a plan, a canal -- Panama")
puts palindrome?("Madam, I'm Adam!")
puts palindrome?("Abracadabra")
