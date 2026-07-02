#include "pch.h"
#include "Clicker.h"
#include "../Toad.h"

#include "Jitter.h"
#include <cmath>

void LeftClicker::StartThread()
{
	m_threadFlag = true;
	m_thread = std::thread(&LeftClicker::Thread, this);
}

void LeftClicker::StopThread()
{
	m_threadFlag = false;
	if (m_thread.joinable())
        m_thread.join();
}

bool LeftClicker::IsThreadAlive() const
{
	return m_threadFlag;
}

void LeftClicker::ResetVars()
{
    this->bonce = false;
    this->counter = 0;
    this->counter2 = 0;
    this->bdrop = false;
    this->boost = false;
    this->boost2 = false;
    this->boost_counter = 0;
    this->boost_counter2 = 0;
    this->first_click = false;
    this->inconsistensy = false;
    this->inconsistensy2 = false;
    this->inconsistensycounter = 0;
    this->inconsistensycounter2 = 0;
}

// handles the randomization and sending clicks
void LeftClicker::SendDown(mouse_type mb, POINT& pt, float& delay, float delayclick2)
{
    this->first_click = true;

    if (this->inconsistensy) {
        delay += toad::random_float(30.f, 100.f);
        this->inconsistensy = false;
    }
    else
        delay = toad::random_float(this->min, this->max);

    if (toad::clicksounds::enabled && !toad::clicksounds::selected_clicksounds.empty())
    {
        selected_clicksound = (size_t)toad::random_int(0, toad::clicksounds::selected_clicksounds.size() - 1);
        auto& sound = toad::clicksounds::selected_clicksounds[selected_clicksound];
		p_SoundPlayer->TriggerSoundPlay(sound.first.string());
    }

    if (toad::clicker::blatant_mode)
    {
        if (toad::misc::compatibility_mode)
        {
            toad::precise_sleep(delayclick2 / 1000);
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds((int)delayclick2));
        }
    }
    else
    {
        if (toad::misc::compatibility_mode)
        {
            toad::precise_sleep(delay / 1000);
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds((int)delay));
        }
    }

    if (toad::jitter::enabled) 
        p_Jitter->DoJitter();             
    
    if (toad::misc::use_mouse_event)
    {
        mb == mouse_type::LEFT ? mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0)
            : mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
    }
    else mb == mouse_type::LEFT ? PostMessage(toad::clicking_window, WM_LBUTTONDOWN, MKF_LEFTBUTTONDOWN, LPARAM((pt.x, pt.y))) :
        PostMessage(toad::clicking_window, WM_RBUTTONDOWN, MKF_RIGHTBUTTONDOWN, LPARAM((pt.x, pt.y)));
}
   
void LeftClicker::SendUp(mouse_type mb, POINT& pt,float& delay, float delayclick2)
{
    if (this->inconsistensy2) {
        delay += toad::random_int(30.f, 100.f);
        this->inconsistensy2 = false;
    }
    else
        delay = toad::random_float(this->min, this->max);

    if (toad::clicker::blatant_mode)
    {
        if (toad::misc::compatibility_mode)
        {
            toad::precise_sleep(delayclick2 / 1000);
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds((int)delayclick2));
        }
    }
    else
    {
        if (toad::misc::compatibility_mode)
        {
            toad::precise_sleep(delay / 1000);
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds((int)delay));
        }
    }

    GetCursorPos(&pt);
    if (toad::misc::use_mouse_event)
    {
        mb == mouse_type::LEFT ? mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0)
            : mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
    }
    else mb == mouse_type::LEFT ? PostMessage(toad::clicking_window, WM_LBUTTONUP, 0, LPARAM((pt.x, pt.y))) :
        PostMessage(toad::clicking_window, WM_RBUTTONUP, 0, LPARAM((pt.x, pt.y)));

    if (toad::clicksounds::enabled && !toad::clicksounds::selected_clicksounds.empty())
    {
		auto& sound = toad::clicksounds::selected_clicksounds[selected_clicksound];
        if (!sound.second.empty())
		    p_SoundPlayer->TriggerSoundPlay(sound.second.string());
    }
	
    this->inconsistensycounter2++;
    this->inconsistensycounter++;
    this->counter++;
    this->boost_counter++;

    if (this->inconsistensycounter2 > 35) {
        if (toad::random_int(0, 100) < 6) { this->inconsistensy2 = true;  this->inconsistensycounter2 = 0; }
    }
    if (this->inconsistensycounter > 25) {
        if (toad::random_int(0, 100) < 6) { this->inconsistensy = true;  this->inconsistensycounter = 0; }
    }

    if (this->boost_counter > toad::random_float(this->mincanboostchance, 25)) {
        if (!this->bdrop && !this->counter2 > 0) {
            this->boost = true;
            this->mincanboostchance = 15;
        }
    }
    if (this->boost) {
        if (toad::clicker::higher_cps) { this->mincandropchance -= 0.5f; }
        else if (!toad::clicker::higher_cps) { this->mincandropchance -= 0.1f; }

        this->boost_counter = 0;
        this->min -= 1.4f;
        this->max += 0.6f;
        this->boost_counter2++;
    }
    if (this->boost_counter2 > 5) {
        this->boost_counter = 0;
        this->boost = false;
        this->boost_counter2++;
        if (boost_counter2 > 45) {
            this->min += 1.4f;
            this->max -= 0.6f;
            if (this->boost_counter2 > 50) {
                this->boost_counter = 0;
                this->boost_counter2 = 0;
                this->counter = 0;
                this->counter2 = 0;
            }
        }
    }
    //drop
    if (this->counter > toad::random_float(this->mincandropchance, 20)) {
        if (!this->boost && !this->boost_counter2 > 0) {
            this->bdrop = true;
            this->mincandropchance = 15;
        }
    }
    if (bdrop) {
        if (!toad::clicker::higher_cps) { this->mincanboostchance -= 0.5f; }
        else if (toad::clicker::higher_cps) { this->mincanboostchance -= 0.1f; }

        this->counter = 0;
        this->max += 1.6f;
        this->counter2++;
    }
    if (this->counter2 > 5) {
        this->counter = 0;
        this->bdrop = false;
        this->counter2++;
        if (this->counter2 > 45) {
            this->max -= 1.6f;
            if (this->counter2 > 50) {
                this->counter = 0;
                this->counter2 = 0;
                this->boost_counter = 0;
                this->boost_counter2 = 0;
            }
        }
    }
}

// main clicker thread
// --------------------------------------------------------------------------------------
// Ported 1:1 from Soda Autoclicker's leftClicker()/clickLeft()/leftClick() (Python).
// Toad's original "humanized" boost/drop/inconsistency drift algorithm has been removed
// entirely and replaced with Soda's much simpler flat/random-delay model. All the other
// Toad features that used to hook into the click cycle (target window, slot whitelist,
// RMB-Lock, click sounds, jitter, compatibility mode, use_mouse_event/PostMessage choice)
// are preserved and still fire at the exact same points as before.
// --------------------------------------------------------------------------------------
void LeftClicker::Thread(){

    POINT pt{};

    SetThreadPriority(m_thread.native_handle(), THREAD_PRIORITY_ABOVE_NORMAL);

    auto sodaSleep = [](float seconds) {
        if (toad::misc::compatibility_mode)
            toad::precise_sleep((double)seconds);
        else
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(seconds * 1000.f)));
    };

    while (m_threadFlag) {

        // --- Soda: compute this cycle's delay (averageCPS based) ---
        float delaySeconds;
        if (toad::clicker::blatant_mode) {
            delaySeconds = 1.0f / (float)toad::clicker::cps;
        } else {
            // Soda: random.random() % (2 / averageCPS)
            float span = 2.0f / (float)toad::clicker::cps;
            delaySeconds = std::fmod(toad::random_float(0.f, 1.f), span);
        }

        // Slot whitelist (kept from Toad, unchanged)
        if (toad::clicker::slot_whitelist && !toad::clicker::whitelisted_slots[toad::clicker::curr_slot]) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            continue;
        }

        // Soda "Hold" mode == Toad's option 0 ("Toggle to Enable"): only click while LMB is physically held
        if (toad::clicker::selected_enable_option == 0 && !(GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
            this->ResetVars();
            sodaSleep(delaySeconds);
            continue;
        }

        // Toad-only option 1 ("Hold to Click"): a separate configurable keybind must be held
        if (toad::clicker::selected_enable_option == 1 && !(GetAsyncKeyState(toad::clicker::keycode) & 0x8000)) {
            this->ResetVars();
            sodaSleep(delaySeconds);
            continue;
        }

        // Soda RMB-Lock: skip the whole cycle while the right mouse button is held
        if (toad::clicker::rmb_lock && (GetAsyncKeyState(VK_RBUTTON) & 0x8000)) {
            sodaSleep(delaySeconds);
            continue;
        }

        // Toad's own window targeting system (Active Window / Minecraft / Custom Window), kept as-is
        if (GetForegroundWindow() != toad::clicking_window) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            continue;
        }

        // Toad's "when mouse visible" (inventory) gating, kept as-is
        if (!toad::clicker::inventory && toad::clicker::cursor_visible) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            continue;
        }

        // --- Soda: click (sound on down, jitter, mouse_event/PostMessage choice all preserved) ---
        if (toad::clicksounds::enabled && !toad::clicksounds::selected_clicksounds.empty())
        {
            selected_clicksound = (size_t)toad::random_int(0, (int)toad::clicksounds::selected_clicksounds.size() - 1);
            auto& sound = toad::clicksounds::selected_clicksounds[selected_clicksound];
            p_SoundPlayer->TriggerSoundPlay(sound.first.string());
        }

        if (toad::jitter::enabled)
            p_Jitter->DoJitter();

        if (toad::misc::use_mouse_event)
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        else
            PostMessage(toad::clicking_window, WM_LBUTTONDOWN, MKF_LEFTBUTTONDOWN, LPARAM((pt.x, pt.y)));

        // Soda: fixed 20ms hold between down and up
        sodaSleep(0.02f);

        if (toad::misc::use_mouse_event)
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        else
            PostMessage(toad::clicking_window, WM_LBUTTONUP, 0, LPARAM((pt.x, pt.y)));

        if (toad::clicksounds::enabled && !toad::clicksounds::selected_clicksounds.empty())
        {
            auto& sound = toad::clicksounds::selected_clicksounds[selected_clicksound];
            if (!sound.second.empty())
                p_SoundPlayer->TriggerSoundPlay(sound.second.string());
        }

        this->first_click = true;

        // --- Soda: wait out the computed CPS delay before the next cycle ---
        sodaSleep(delaySeconds);
    }
}

void RightClicker::StartThread()
{
	m_threadFlag = true;
	m_thread = std::thread(&RightClicker::ThreadRight, this);
}

void RightClicker::StopThread()
{
	m_threadFlag = false;
	if (m_thread.joinable())  m_thread.join();
}

bool RightClicker::IsThreadAlive() const
{
	return m_threadFlag;
}

void RightClicker::ThreadRight()
{
	bool playsoundFlag = false;
	POINT pt;
	constexpr auto mb = mouse_type::RIGHT;

	float delaymin, delaymax;
	float delayclick, blatantdelay;

	SetThreadPriority(m_thread.native_handle(), THREAD_PRIORITY_ABOVE_NORMAL);

	while (m_threadFlag) {
		//cpu
	   // if (!toad::clicker::r::right_enabled) { std::this_thread::sleep_for(std::chrono::milliseconds(100)); }
		// unnesesarry checks (thread is active when enabled is true)
	   // else {

		if (!this->can_stop) { std::this_thread::sleep_for(std::chrono::milliseconds(50)); continue; }
		if (toad::clicker::r::right_only_inventory && !toad::clicker::cursor_visible) { std::this_thread::sleep_for(std::chrono::milliseconds(50)); continue; }
		if (!toad::clicker::r::right_inventory && toad::clicker::cursor_visible) { std::this_thread::sleep_for(std::chrono::milliseconds(50)); continue; }

		if (GetForegroundWindow() == toad::clicking_window)
		{
			if (!GetAsyncKeyState(VK_RBUTTON))
			{
				//if (toad::clicksounds::enabled && !playsoundFlag)
				//{
				//	p_SoundPlayer->TriggerSoundPlay();
				//	playsoundFlag = true;
				//}

				this->ResetVars();
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}

			delaymin = 1000.f / (float)toad::clicker::r::right_maxcps / 2.f;
			delaymax = 1000.f / (float)toad::clicker::r::right_mincps / 2.f;

			delayclick = toad::random_float(delaymin - 0.6f, delaymax + 1.f);
			blatantdelay = toad::random_float(delaymin, delaymax);
if (!this->bonce)
			{
				this->min = delaymin;
				this->max = delaymax;
				this->bonce = true;
			}
			else
			{
				if (this->min < delaymin) this->min = delaymin;
				if (this->max > delaymax) this->max = delaymax;
			}
			switch (toad::clicker::r::right_selected_enable_option)
			{
			case 0:
			{
				if (GetAsyncKeyState(VK_RBUTTON))
				{
					playsoundFlag = false;
					//delay on first click
					if (!this->first_click)
					{
						std::this_thread::sleep_for(std::chrono::milliseconds(int(delayclick) + 10));
						first_click = true;
					}
				}

				if (GetAsyncKeyState(VK_RBUTTON))
				{
					SendDown(mb, pt, blatantdelay, delayclick);
					SendUp(mb, pt, blatantdelay, delayclick);
				}
			}
			break;

			case 1:
			{
				if (GetAsyncKeyState(toad::clicker::r::right_keycode))
				{
					SendDown(mb, pt, blatantdelay, delayclick);
					SendUp(mb, pt, blatantdelay, delayclick);
				}
				else
				{
					this->ResetVars();
				}
			}
			break;

			default:
				SendDown(mb, pt, blatantdelay, delayclick);
				SendUp(mb, pt, blatantdelay, delayclick);
				break;
			}
		}
		//cpu
		else std::this_thread::sleep_for(std::chrono::milliseconds(500));
		// }
	}
}
