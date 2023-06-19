#include "Branch.h"

Branch::Branch(sf::Texture& tex, sf::Vector2f spriteDir, 
    const std::string& n, const sf::Vector2f p)
    :SpriteGo(tex, spriteDir, n, p), tree(nullptr), side(Sides::None)
{
}

Branch::~Branch()
{
}

void Branch::Init()
{
    sf::Vector2f treeSize = tree->GetSize();
    sf::Vector2f branchSize = GetSize();

    sprite.setOrigin(-treeSize.x * 0.5f, branchSize.y * 0.5f);
}

void Branch::SetTree(SpriteGo* tree)
{
    this->tree = tree;
}

void Branch::SetSide(Sides side)
{
    this->side = side;
    switch (this->side)
    {
    case Sides::Left:
        //SetFlipX(true);
        SetFlipX(false);
        break;
    case Sides::Right:
        //SetFlipX(false);
        SetFlipX(true);
        break;
    }
}

Sides Branch::GetSide() const
{
    return side;
}
