class Dessert
  attr_accessor :name, :calories
  def initialize(name, calories)
    @name = name
    @calories = calories
  end
  
  def healthy?
    @calories < 200
  end

  def delicious?
    true
  end
end

class JellyBean < Dessert
  attr_accessor :flavor
  def initialize(name, calories, flavor)
    super(name, calories)
    @flavor = flavor
  end

  def delicious?
    if @flavor == "black licorice"
      false
    else
      super
    end
  end
end

a = JellyBean.new("a", 200, "efe")
b = JellyBean.new("b", 20, "black licorice")
puts a.healthy?
puts a.delicious?

puts b.healthy?
puts b.delicious?
