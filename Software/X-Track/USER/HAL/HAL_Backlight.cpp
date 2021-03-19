#include "Display/Display.h"
#include "HAL.h"

/**
  * @brief  �������Ƚ��䣬��lv_anim����
  * @param  obj:����
  * @param  brightness:����ֵ
  * @retval None
  */
static void Backlight_AnimCallback(void * obj, int16_t brightness)
{
    HAL::Backlight_SetValue(brightness);
}

/**
  * @brief  �����ʼ��
  * @param  ��
  * @retval ��
  */
void HAL::Backlight_Init()
{
    /*PWM��ʼ����1000����20KƵ��*/
    PWM_Init(SCREEN_BLK_PIN, 1000, 20000);
}

/**
  * @brief  �������ã�����Ч��
  * @param  target:Ŀ������(0~1000 -> 0~100%)
  * @retval ��
  */
void HAL::Backlight_SetGradual(uint16_t target, uint16_t time)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)Backlight_AnimCallback);
    lv_anim_set_values(&a, Backlight_GetValue(), target);
    lv_anim_set_time(&a, time);
    
    lv_anim_path_t path;
    lv_anim_path_init(&path);
    lv_anim_path_set_cb(&path, lv_anim_path_ease_out);
    lv_anim_set_path(&a, &path);
    
    lv_anim_start(&a);
}

/**
  * @brief  ��ȡ��������
  * @param  ��
  * @retval ��ǰ����(0~1000 -> 0~100%)
  */
uint16_t HAL::Backlight_GetValue()
{
    return timer_get_compare(PIN_MAP[SCREEN_BLK_PIN].TIMx, PIN_MAP[SCREEN_BLK_PIN].TimerChannel);
}

/**
  * @brief  ���ñ�������
  * @param  val: ����(0~1000 -> 0~100%)
  * @retval ��
  */
void HAL::Backlight_SetValue(int16_t val)
{
    __LimitValue(val, 0, 1000);
    analogWrite(SCREEN_BLK_PIN, val);
}

/**
  * @brief  �Ӻ󱸼Ĵ�����ȡ���籣��ı�������
  * @param  ��
  * @retval ����(0~1000 -> 0~100%)
  */
uint16_t HAL::Backlight_GetBKP()
{
    uint16_t value = 0;
    
    /*����ֵ�Ƿ�Ƿ�*/
    if(value == 0 || value > 1000)
    {
        /*����Ĭ������*/
        value = 1000;
    }
    
    return value;
}

/**
  * @brief  ����ǰ���ȸ������󱸼Ĵ���
  * @param  ��
  * @retval ��
  */
void HAL::Backlight_UpdateBKP()
{
}
