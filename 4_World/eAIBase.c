modded class eAIBase
{
    static ref array<eAIBase> d_All = {};
    
    void eAIBase()
    {
        if (!d_All) {
            d_All = {};
        }
        
        d_All.Insert(this);
    }
    
    void ~eAIBase()
    {
        if (d_All) {
            d_All.RemoveItem(this);
        }
    }
    
    static bool IsInVicinity(EntityAI entity, int range = 100)
    {
        range *= range;
        vector position = entity.GetPosition();
        
        foreach (eAIBase eai_base: d_All) {
            if (vector.Distancesq(eai_base.GetPosition(), position) < range) {
                return true;
            }
        }
        
        return false;
    }
}