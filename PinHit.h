#ifndef PINHIT_H_
#define PINHIT_H_

class PinHit {
  

 private:

  int m_pin, m_hits;

 public:
  PinHit();
  PinHit(int key, int value);

  void SetKey(int pin);
  int GetKey() const;
  int GetValue() const;
  void IncHits();
  int CompareTo(const PinHit& comparedPin);
  bool operator==(const PinHit& other);
};

#endif /* PinHit_H_ */
