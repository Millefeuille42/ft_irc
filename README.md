# Norm-IRC-Net
### <a href="">Sujet</a>

## Règles de contribution

- `master`
  - Ne pas push sur `master`, faire des PR, préférablement depuis la branche `devel`
  - Pour merge, il faut que la branche source de la PR soit a jour avec `master`, seulement en avance, pas en retard
  - Pour merge, la PR doit être approuvée par 3 collaborateurs
  - Pour merge, le code de chaque PR doit compiler avec `make` et être validée par GitGuardian (automatique)
  - Si un commit est fait sur la branche source, la PR est invalidée

- `devel`
  - Ne pas push sur `devel` faire des PR
  - Aucune autre restriction ne s'applique

## Comment faire des branches
Changer de branche
```
git checkout <branche>
```

Créer une branche et passer dessus

```
git checkout -b <branche>
```

Il faut d'abord aller sur la branche source, en général `devel`. <br>
Ensuite il suffite de créer sa branche.

Pour push sur le remote (Github), vous savez déjà faire, c'est comme vous avez toujours fait.

Simplement, si la branche a seulement été créee localement, faites votre premier push avec la commande
```
git push --set-upstream origin <branche>
```
