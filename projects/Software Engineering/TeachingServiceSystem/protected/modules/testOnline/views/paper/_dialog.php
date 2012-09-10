<?php
$this->beginWidget('zii.widgets.jui.CJuiDialog', array(
    'id'=>'mydialog',
    // additional javascript options for the dialog plugin
    'options'=>array(
        'title'=>'Add Questions',
        'autoOpen'=>false,
        'width'=>'auto',
        'height'=>'auto',
    ),
));

$this->widget('zii.widgets.grid.CGridView', array(
    'id'=>'question-bank-grid',
    'dataProvider'=>PaperBankController::getUnusedQuestions(),
    'filter'=>QuestionBank::model(),

    'columns'=>array(
        'id',
        'question',
        'selection_a',
        'selection_b',
        'selection_c',
        'selection_d',
        'type',
        'answer',
        array(
            'class'=>'CCheckBoxColumn',
            'selectableRows'=>2,
        ),
    ),
));

$this->endWidget('zii.widgets.jui.CJuiDialog');

// the link that may open the dialog
echo CHtml::link('Add Questions Manually', '#', array(
   'onclick'=>'$("#mydialog").dialog("open"); return false;',
));
?>