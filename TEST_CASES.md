# Rain-Sensing Wiper System - Test Cases

## Overview
This document contains comprehensive test cases for the Rain-Sensing Wiper System to verify all functionality and edge cases.

## Test Environment Setup
- **Executable**: `WiperSystemPureAuto.exe`
- **Operating System**: Windows
- **Test Method**: Manual testing with keyboard inputs
- **Expected Behavior**: Real-time system responses with colored output

---

## 1. SYSTEM INITIALIZATION TESTS

### TC-001: Initial Mode Selection
**Objective**: Verify system starts correctly and allows mode selection
**Steps**:
1. Run `WiperSystemPureAuto.exe`
2. Observe initialization screen
3. Test invalid input (e.g., '3', 'a', etc.)
4. Select '1' for Manual Mode
5. Select '2' for Auto Mode

**Expected Results**:
- System displays initialization screen with options 1 and 2
- Invalid inputs show error message and retry
- Valid selection proceeds to next step
- Manual mode shows wiper speed selection
- Auto mode starts directly

### TC-002: Manual Mode Initial Setup
**Objective**: Verify manual mode initialization
**Steps**:
1. Select Manual Mode (option 1)
2. Test invalid wiper speed (e.g., '9', 'a')
3. Select each valid option (0-3)

**Expected Results**:
- Shows wiper speed options 0-3
- Invalid inputs show error and retry
- Each valid selection sets appropriate wiper speed
- System starts with selected configuration

---

## 2. AUTO MODE TESTS

### TC-003: Basic Rain Detection
**Objective**: Verify automatic wiper speed adjustment based on rain intensity
**Steps**:
1. Start in Auto Mode
2. Observe system behavior for 30 seconds
3. Note different sensor readings and corresponding wiper speeds

**Expected Results**:
- Sensor readings 80%+ → Wiper OFF
- Sensor readings 50-79% → Wiper LOW
- Sensor readings 20-49% → Wiper MEDIUM
- Sensor readings <20% → Wiper HIGH
- Display format: `[Time] Mode: AUTO | Sensor: X% | Wiper: SPEED`

### TC-004: 10-Second Turn-Off Delay
**Objective**: Verify wipers don't turn off immediately when rain stops
**Steps**:
1. Start in Auto Mode
2. Wait for wipers to activate (sensor <80%)
3. Wait for sensor to read 80%+ (conditions for turning off)
4. Observe countdown timer
5. Verify wipers stay on during countdown
6. Verify wipers turn off after 10 seconds

**Expected Results**:
- When conditions suggest turning off, countdown appears: `(Turning OFF in Xs)`
- Countdown decreases from 10 to 1
- Wipers remain at current speed during countdown
- After 10 seconds, wipers turn OFF

### TC-005: Rain Detection During Turn-Off Countdown
**Objective**: Verify countdown cancellation when rain detected again
**Steps**:
1. Start in Auto Mode
2. Wait for turn-off countdown to start
3. Wait for sensor to detect rain again (reading <80%)
4. Verify countdown cancellation and immediate speed adjustment

**Expected Results**:
- Countdown message disappears immediately
- Wiper speed adjusts to new rain intensity immediately
- No delay in response to new rain detection

### TC-006: Sudden Rain Burst Detection
**Objective**: Verify immediate HIGH speed activation for sudden rain
**Steps**:
1. Start in Auto Mode
2. Wait for sudden rain burst detection (random event)
3. Observe immediate response

**Expected Results**:
- Display shows: `(Sudden Rain Burst)`
- Wiper speed immediately set to HIGH
- Any pending turn-off countdown cancelled

### TC-007: Sensor Failure Handling
**Objective**: Verify system behavior during sensor failures
**Steps**:
1. Start in Auto Mode
2. Wait for sensor failure event (random)
3. Observe system response

**Expected Results**:
- Display shows: `Mode: AUTO | Sensor: ERROR | Wiper: LOW (Sensor Failure - Switch to Manual)`
- Wiper speed set to LOW as safety measure
- Any pending turn-off countdown cancelled

---

## 3. MANUAL MODE TESTS

### TC-008: Basic Wiper Speed Control
**Objective**: Verify manual wiper speed changes
**Steps**:
1. Start in Manual Mode
2. Test each speed: Press '0', '1', '2', '3'
3. Verify immediate response for each

**Expected Results**:
- '0': Wiper OFF, spray cleared, message: "Manual: Wiper set to OFF (spray cleared)"
- '1': Wiper LOW, spray preserved, message: "Manual: Wiper set to LOW (spray preserved)"
- '2': Wiper MEDIUM, spray preserved, message: "Manual: Wiper set to MEDIUM (spray preserved)"
- '3': Wiper HIGH, spray preserved, message: "Manual: Wiper set to HIGH (spray preserved)"

### TC-009: Spray Preservation During Speed Changes
**Objective**: Verify spray remains active when changing wiper speeds (except OFF)
**Steps**:
1. Start in Manual Mode, select speed '1'
2. Activate light spray: Press 's'
3. Change wiper speeds: Press '2', then '3', then '1'
4. Verify spray remains active
5. Press '0' and verify spray is cleared

**Expected Results**:
- Spray remains active during speed changes 1→2→3→1
- Status shows: `Mode: MANUAL | Wiper: SPEED | Spray: LIGHT SPRAY`
- When pressing '0', spray is cleared and status shows no spray

### TC-010: Independent Spray Controls
**Objective**: Verify spray controls work independently of wiper speed
**Steps**:
1. Start in Manual Mode, select speed '2'
2. Test light spray toggle: Press 's' (on), 's' (off)
3. Test heavy spray toggle: Press 'S' (on), 'S' (off)
4. Test spray combinations: 's' (light), 'S' (heavy), 'x' (off)

**Expected Results**:
- 's': Toggles light spray on/off, messages: "Light spray activated/turned OFF (wipers continue)"
- 'S': Toggles heavy spray on/off, messages: "Heavy spray activated/turned OFF (wipers continue)"
- 'x': Turns off any spray, message: "Water spray turned OFF (wipers continue)"
- Wiper speed remains unchanged during all spray operations

### TC-011: Dew Detection Display (Manual Only)
**Objective**: Verify dew detection information appears only in manual mode
**Steps**:
1. Start in Manual Mode
2. Wait for dew detection event
3. Switch to Auto Mode
4. Verify dew information disappears
5. Switch back to Manual Mode
6. Verify dew information reappears

**Expected Results**:
- Manual Mode: Shows `(Dew Detected: X%)`
- Auto Mode: No dew information displayed
- Manual Mode again: Dew information visible again

---

## 4. MODE SWITCHING TESTS

### TC-012: Manual to Auto Mode Switch
**Objective**: Verify proper transition from Manual to Auto mode
**Steps**:
1. Start in Manual Mode
2. Set wiper speed to '2' and activate spray 's'
3. Press 'a' to switch to Auto Mode
4. Verify spray is cleared and auto operation begins

**Expected Results**:
- Message: "Switched to AUTO mode (spray cleared)"
- Spray status disappears from display
- Auto mode rain detection begins
- Wiper speed adjusts based on sensor readings

### TC-013: Auto to Manual Mode Switch
**Objective**: Verify proper transition from Auto to Manual mode
**Steps**:
1. Start in Auto Mode
2. Wait for wipers to activate
3. Press 'm' to switch to Manual Mode
4. Select initial wiper speed

**Expected Results**:
- Message: "Switched to MANUAL mode"
- Manual wiper speed selection menu appears
- Selected speed is applied
- Manual controls become active

### TC-014: Mode Switch During Turn-Off Countdown
**Objective**: Verify countdown cancellation when switching modes
**Steps**:
1. Start in Auto Mode
2. Wait for turn-off countdown to begin
3. Press 'm' to switch to Manual Mode during countdown

**Expected Results**:
- Countdown immediately cancelled
- Switch to Manual Mode proceeds normally
- Manual speed selection menu appears

---

## 5. EDGE CASES AND ERROR HANDLING

### TC-015: Rapid Input Testing
**Objective**: Verify system handles rapid key presses
**Steps**:
1. Start in Manual Mode
2. Rapidly press different keys: '1', '2', '3', 's', 'S', 'x'
3. Verify system responds correctly to each input

**Expected Results**:
- Each input processed correctly
- No system crashes or unexpected behavior
- Status updates reflect all changes

### TC-016: Invalid Key Presses
**Objective**: Verify system ignores invalid inputs during operation
**Steps**:
1. Start system in any mode
2. Press invalid keys: '4', '5', '6', 'z', 'enter', 'space'
3. Verify system continues normal operation

**Expected Results**:
- Invalid keys are ignored
- System continues normal operation
- No error messages or crashes

### TC-017: Continuous Operation Test
**Objective**: Verify system stability during extended operation
**Steps**:
1. Start in Auto Mode
2. Let system run for 5 minutes
3. Observe for memory leaks, crashes, or performance issues
4. Switch modes multiple times during operation

**Expected Results**:
- System runs continuously without issues
- Memory usage remains stable
- All functions continue to work correctly

### TC-018: Spray Controls in Auto Mode (Should Be Disabled)
**Objective**: Verify spray controls don't work in Auto Mode
**Steps**:
1. Start in Auto Mode
2. Try spray controls: Press 's', 'S', 'x'
3. Verify no spray activation or messages

**Expected Results**:
- Spray control keys ('s', 'S', 'x') are ignored in Auto Mode
- No spray status appears in display
- No spray-related messages generated

---

## 6. DISPLAY AND UI TESTS

### TC-019: Status Display Format Verification
**Objective**: Verify correct display format for all modes and conditions
**Steps**:
1. Test Auto Mode display format
2. Test Manual Mode display format
3. Test special condition displays (sudden rain, dew, countdown, errors)

**Expected Results**:
**Auto Mode Format**:
```
[HH:MM:SS] Mode: AUTO | Sensor: X% | Wiper: SPEED
[HH:MM:SS] Mode: AUTO | Sensor: X% | Wiper: SPEED (Sudden Rain Burst)
[HH:MM:SS] Mode: AUTO | Sensor: X% | Wiper: SPEED (Turning OFF in Xs)
[HH:MM:SS] Mode: AUTO | Sensor: ERROR | Wiper: SPEED (Sensor Failure - Switch to Manual)
```

**Manual Mode Format**:
```
[HH:MM:SS] Mode: MANUAL | Wiper: SPEED
[HH:MM:SS] Mode: MANUAL | Wiper: SPEED | Spray: SPRAY_TYPE
```

### TC-020: Color Coding Verification
**Objective**: Verify correct color coding for different elements
**Steps**:
1. Observe colors for different wiper speeds
2. Observe colors for different modes
3. Observe colors for different message types

**Expected Results**:
- **Wiper Speeds**: OFF (Gray), LOW (Green), MEDIUM (Yellow), HIGH (Red)
- **Modes**: AUTO (Green), MANUAL (Blue)
- **Messages**: Timestamps (Cyan), Errors (Red), Warnings (Yellow), Spray (Cyan/Blue)

---

## 7. INTEGRATION TESTS

### TC-021: Complete Workflow Test
**Objective**: Test complete system workflow with all features
**Steps**:
1. Start in Auto Mode
2. Wait for various rain conditions and responses
3. Switch to Manual Mode during operation
4. Test all manual controls and spray functions
5. Switch back to Auto Mode
6. Test turn-off delay and countdown cancellation
7. Quit system gracefully

**Expected Results**:
- All transitions work smoothly
- No data loss between mode switches
- All features function correctly in sequence
- System exits cleanly with 'q'

### TC-022: Stress Test Scenario
**Objective**: Test system under rapid condition changes
**Steps**:
1. Start in Auto Mode
2. Rapidly switch between modes multiple times
3. In Manual Mode, rapidly change speeds and spray settings
4. Test during various sensor conditions

**Expected Results**:
- System handles all rapid changes correctly
- No crashes or unexpected behavior
- All state changes are properly managed

---

## 8. ACCEPTANCE CRITERIA VERIFICATION

### TC-023: Requirements Compliance Check
**Objective**: Verify all specified requirements are met

**Auto Mode Requirements**:
- [REQUIRED] Rain detection with appropriate wiper speeds
- [REQUIRED] 10-second delay before turning off wipers
- [REQUIRED] Countdown cancellation when rain detected
- [REQUIRED] Sudden rain burst immediate response
- [REQUIRED] Sensor failure safety mode
- [REQUIRED] No dew detection or spray functionality
- [REQUIRED] No manual spray controls

**Manual Mode Requirements**:
- [REQUIRED] Full wiper speed control (0-3)
- [REQUIRED] Independent spray controls (s, S, x)
- [REQUIRED] Spray preservation during speed changes (except OFF)
- [REQUIRED] Dew detection display
- [REQUIRED] All controls responsive and immediate

**General Requirements**:
- [REQUIRED] Mode switching functionality
- [REQUIRED] Clean, colored display output
- [REQUIRED] Graceful system exit
- [REQUIRED] No crashes or memory leaks

---

## Test Execution Checklist

### Pre-Test Setup
- [ ] Compile latest version: `g++ -Wall -Wextra -Wpedantic -std=c++11 main.cpp ColorUtilities.cpp WiperEnums.cpp RainSensor.cpp WindshieldWiperController.cpp WiperSystemManager.cpp -o WiperSystemPureAuto.exe`
- [ ] Verify executable exists: `WiperSystemPureAuto.exe`
- [ ] Clear terminal for clean test environment

### Test Execution Order
1. [ ] System Initialization Tests (TC-001, TC-002)
2. [ ] Auto Mode Tests (TC-003 through TC-007)
3. [ ] Manual Mode Tests (TC-008 through TC-011)
4. [ ] Mode Switching Tests (TC-012 through TC-014)
5. [ ] Edge Cases (TC-015 through TC-018)
6. [ ] Display Tests (TC-019, TC-020)
7. [ ] Integration Tests (TC-021, TC-022)
8. [ ] Acceptance Criteria (TC-023)

### Test Results Documentation
For each test case, document:
- **Status**: PASS/FAIL
- **Actual Result**: What actually happened
- **Issues Found**: Any deviations from expected behavior
- **Screenshots**: If applicable
- **Notes**: Additional observations

---

## Known Test Scenarios

### Typical Auto Mode Sequence
```
[16:45:01] Mode: AUTO | Sensor: 85% | Wiper: OFF
[16:45:02] Mode: AUTO | Sensor: 45% | Wiper: MEDIUM
[16:45:03] Mode: AUTO | Sensor: 15% | Wiper: HIGH (Sudden Rain Burst)
[16:45:04] Mode: AUTO | Sensor: 85% | Wiper: HIGH (Turning OFF in 10s)
[16:45:05] Mode: AUTO | Sensor: 85% | Wiper: HIGH (Turning OFF in 9s)
...
[16:45:14] Mode: AUTO | Sensor: 85% | Wiper: OFF
```

### Typical Manual Mode Sequence
```
[16:45:01] Manual: Wiper set to LOW (spray preserved)
[16:45:02] Light spray activated (wipers continue)
[16:45:03] Mode: MANUAL | Wiper: LOW | Spray: LIGHT SPRAY
[16:45:04] Manual: Wiper set to MEDIUM (spray preserved)
[16:45:05] Mode: MANUAL | Wiper: MEDIUM | Spray: LIGHT SPRAY
```

This comprehensive test plan covers all functionality and edge cases of your Rain-Sensing Wiper System. Execute these tests systematically to ensure complete system validation.