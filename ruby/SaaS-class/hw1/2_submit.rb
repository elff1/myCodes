class WrongNumberOfPlayersError < StandardError ; end
class NoSuchStrategyError < StandardError ; end

def rps_game_winner(game)
  raise WrongNumberOfPlayersError unless game.length == 2
  game.each do |player|
    raise NoSuchStrategyError unless player[1] =~ /^[RPS]$/
  end
  if game[0][1] == game[1][1]
    @winner = 0
  elsif game[0][1] == "R"
    if game[1][1] == "S"
      @winner = 0
    else
      @winner = 1
    end
  elsif game[0][1] == "P"
    if game[1][1] == "R"
      @winner = 0
    else
      @winner = 1
    end
  elsif game[0][1] == "S"
    if game[1][1] == "P"
      @winner = 0
    else
      @winner = 1
    end
  end
  #puts @winner
  game[@winner]
end

def rps_tournament_winner(tournament)
  if tournament[0][0].class == String
    rps_game_winner(tournament)
  else
    a = rps_tournament_winner(tournament[0])
    b = rps_tournament_winner(tournament[1])
    rps_game_winner([a, b])
  end
end