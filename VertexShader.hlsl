
float4 vsmain(float4 position : POSITION) : SV_POSITION 
{
    if (position.y > 0 && position.y < 1)
    {
        position.x += 0.25f; // Move the vertex to the right by 0.25 units if it's within the specified y range
    }
    
    if (position.y > -1 && position.y < 0 && position.x > 0 && position.x < 1)
    {
        position.y += 0.25f; // Move the vertex to the right by 0.25 units if it's within the specified y range
    }
    
    if (position.y > 0 && position.y < 1 && position.x > -1 && position.x < 0)
    {
        position.y -= 0.25f; // Move the vertex to the right by 0.25 units if it's within the specified y range
    }
    
    return position; // Pass the vertex position through to the pixel shader
}


/*
float4 psmain(float4 position : SV_POSITION) : SV_Target
{
    return float4(0.8f, 0.9f, 0.4f, 1.0f);
}
*/