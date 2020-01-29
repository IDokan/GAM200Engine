void StringPhysics::LimitStringLength()
{
    if (stringPhysicsOwner->GetStringLength() > limitStringLength)
    {
        if (stringPhysicsOwner->oldStringLength < stringPhysicsOwner->stringLength)
        {
            int friction = stringPhysicsOwner->stringLength / 100;
            DetermineFrcition(friction);
        }
        else
        {
            player1->GetComponentByTemplate<Physics>()->SetFriction(1.f);
            player2->GetComponentByTemplate<Physics>()->SetFriction(1.f);
        }
    }
    else
    {
        player1->GetComponentByTemplate<Physics>()->SetFriction(1.f);
        player2->GetComponentByTemplate<Physics>()->SetFriction(1.f);
    }
}

void StringPhysics::DetermineFrcition(int friction)
{
    switch(friction)
    {
    case 5:
        player1->GetComponentByTemplate<Physics>()->SetFriction(0.7f);
        player2->GetComponentByTemplate<Physics>()->SetFriction(0.7f);
        break;
    case 6:
        player1->GetComponentByTemplate<Physics>()->SetFriction(0.5f);
        player2->GetComponentByTemplate<Physics>()->SetFriction(0.5f);
        break;
    case 7:
        player1->GetComponentByTemplate<Physics>()->SetFriction(0.3f);
        player2->GetComponentByTemplate<Physics>()->SetFriction(0.3f);
        break;
    default:
        player1->GetComponentByTemplate<Physics>()->SetFriction(0.1f);
        player2->GetComponentByTemplate<Physics>()->SetFriction(0.1f);
        break;
    }
}


void StringPhysics::LimitStringLength() 
{ 
    if (string->GetStringLength() > 1000.f) 
    { 
        object1->GetComponentByTemplate<Physics>()->SetIsCollide(true); 
        object2->GetComponentByTemplate<Physics>()->SetIsCollide(true); 
 
        object1->GetComponentByTemplate<Physics>()->SetPosition(object1->GetComponentByTemplate<Physics>()->GetOldPosition()); 
        object2->GetComponentByTemplate<Physics>()->SetPosition(object2->GetComponentByTemplate<Physics>()->GetOldPosition()); 
    } 
} 