# ft_irc

## RTFM
### <a href="https://cdn.intra.42.fr/pdf/pdf/47620/fr.subject.pdf">Sujet</a>
### <a href="http://abcdrfc.free.fr/rfc-vf/rfc1459.html" Norme RFC de référence pour IRC>

## Client IRC
On va utiliser le client `irssi`, pour l'installer il faut d'abord installer brew, avec la commande suivante:
```
rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update
```

Ensuite installer irssi
```
brew install irssi
```

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

Delete une branche localement
```
git branch -d <branche>
```

Lister les branches remotes
```
git branch -r
```

Push votre branche sur le remote (a faire des sa creation)
```
git push --set-upstream origin <branche>
```

Merge une branche dans la branche dans laquelle vous etes
```
git merge <source>
```

Il faut d'abord aller sur la branche source, en général `devel`. <br>
Ensuite il suffite de créer sa branche.

Pour push sur le remote (Github), vous savez déjà faire, c'est comme vous avez toujours fait.

Simplement, si la branche a seulement été créee localement, faites votre premier push avec la commande
```
git push --set-upstream origin <branche>
```

### Comment faire un merge local
Si vous voulez merge une branche localement, allez dans la branche cible, celle DANS laquelle vous voulez merge, puis faites la commande 
```
git merge <source>
```

Ceci dit, preferez les merges via Github, si ca concerne des branches ou vous travaillez a plusieurs dessus
