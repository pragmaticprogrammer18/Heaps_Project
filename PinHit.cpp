#include "PinHit.h"

PinHit::PinHit() {
  m_pin = -1;
  m_hits = 0;
}

PinHit::PinHit(int key, int value) {
  m_pin = key;
  m_hits = value;
}

void PinHit::SetKey(int pin) {
  m_pin = pin;
}

int PinHit::GetKey() const {
  return m_pin;
}

int PinHit::GetValue() const {
  return m_hits;
}

void PinHit::IncHits() {
  m_hits++;
}

int PinHit::CompareTo(const PinHit& other) {
  //0 if same
  //-1 if this < other
  // 1 if this > other

  return (m_hits - other.GetValue());
}


bool PinHit::operator==(const PinHit& other){
  return (GetKey() == other.GetKey());
}


