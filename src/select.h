class Select {
public:
  Select() = delete;

  template<typename Iter>
  static Iter HoareSelect(Iter begin, Iter end, long k);
  
  template<typename Iter>
  static Iter MagicFiveSelect(Iter begin, Iter end, long k);
};