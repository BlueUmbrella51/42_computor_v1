// template class, coefficient can be multiple types
template <typename T> class Token // not sure if int works
{
  public:
    // template variable
    T       _coeff;
    int     _degree;
    // template member function
    template<typename U>
    void mf(const U &u)
    {

    }
};
