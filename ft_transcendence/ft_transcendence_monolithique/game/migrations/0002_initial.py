
import django.db.models.deletion
from django.conf import settings
from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
        ('game', '0001_initial'),
        migrations.swappable_dependency(settings.AUTH_USER_MODEL),
    ]

    operations = [
        migrations.AddField(
            model_name='gamesession',
            name='player1',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, related_name='games_as_player1', to=settings.AUTH_USER_MODEL),
        ),
        migrations.AddField(
            model_name='gamesession',
            name='player2',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, related_name='games_as_player2', to=settings.AUTH_USER_MODEL),
        ),
        migrations.AddField(
            model_name='tournament',
            name='creator',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, related_name='created_tournaments', to=settings.AUTH_USER_MODEL),
        ),
        migrations.AddField(
            model_name='tournament',
            name='players',
            field=models.ManyToManyField(related_name='tournaments', to=settings.AUTH_USER_MODEL),
        ),
        migrations.AddField(
            model_name='tournamentmatch',
            name='player1',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, related_name='tournament_matches_as_player1', to=settings.AUTH_USER_MODEL),
        ),
        migrations.AddField(
            model_name='tournamentmatch',
            name='player2',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, related_name='tournament_matches_as_player2', to=settings.AUTH_USER_MODEL),
        ),
        migrations.AddField(
            model_name='tournamentmatch',
            name='tournament',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='game.tournament'),
        ),
        migrations.AddField(
            model_name='tournamentmatch',
            name='winner',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.SET_NULL, related_name='won_matches', to=settings.AUTH_USER_MODEL),
        ),
    ]
