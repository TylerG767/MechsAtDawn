# Mechs At Dawn (Working Title)
A mech theme bullethell game

## Project Status
This project is in **early development**. The current stage implements:
- Basic player movement and controls
- Enemy spawning and simple attack mechanics
- Experience and leveling system
- Upgrade system with single-choice upgrades
- Initial integration of data-driven prompts (Windsurf) for generating upgrade ideas

## Current Features
1. **Core Gameplay Loop**
   - Player moves around the map and fights waves of enemies.
   - Enemies drop experience orbs on defeat.
   - Player can level up by collecting experience.

2. **Upgrade System (Stage 1)**
   - On level-up, the player can choose an upgrade.
   - Upgrade options currently come from a generated list.
   - System supports adding new upgrade types.

3. **Technical Setup**
   - Written in C++.
   - Modular design for expanding enemy behaviors, player abilities, and upgrade logic.
   - Code structured for iteration and testing.

## Next Steps
- **Implement Branching Upgrade Tree**  
  Move beyond single-choice upgrades. Players will progress along a branching path, where upgrades unlock new upgrade possibilities instead of being isolated.  

- **Enhance Upgrade Variety**  
  Add more upgrade types (weapons, passive boosts, utility effects) to enrich gameplay.  

- **Improve Enemy AI**  
  Implement varied behaviors (chasing, ranged attacks, special patterns).  

- **Balancing & Scaling**  
  Introduce scaling difficulty, enemy strength progression, and pacing adjustments.  

- **UI/UX**  
  Add menus, health/XP indicators, and level-up choice screens.  

---

## Roadmap
- [x] Core movement and combat  
- [x] Experience and leveling system  
- [x] Single-choice upgrade system  
- [ ] Branching upgrade tree  
- [ ] Expanded upgrade pool  
- [ ] Enemy AI improvements  
- [ ] UI polish  

---
